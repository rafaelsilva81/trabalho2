#include "OpenTextures.h"
//---------------------------------------------------------------------------
/*
struct my_error_mgr
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr * my_error_ptr;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp(myerr->setjmp_buffer, 1);
}
//*/
//---------------------------------------------------------------------------
ILuint OpenTextures::LoadImage(const char *filename)
{
    ILboolean success;
    ILuint image;

    ilGenImages(1, &image); /* Generation of one image name */
    ilBindImage(image); /* Binding of image name */
    success = ilLoadImage(filename); /* Loading of the image filename by DevIL */

    if (success) /* If no error occured: */
    {
        /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        if (!success)
        {
            return -1;
        }
    }
    else
        return -1;

    return image;
}
//---------------------------------------------------------------------------
void OpenTextures::loadTexture(const char *filename, int wrap)
{
//*
    /* load the file picture with DevIL */
        ILuint image = LoadImage(filename);
        if ( image == -1 )
        {
            printf("Can't load picture file %s by DevIL \n", filename);
            return;
        }

    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
              0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */

    //gluBuild2DMipmaps( GL_TEXTURE_2D, 3, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
    //                   ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData() );

    ilDeleteImages(1, &image); /* Because we have already copied image data into texture data we can release memory used by image. */

  // Set Texture mapping parameters
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //GL_REPLACE, GL_MODULATE, GL_BLEND

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST, GL_LINEAR
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP ); //GL_CLAMP : GL_REPEAT
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
//*/
}
//---------------------------------------------------------------------------
void OpenTextures::loadTextureRAW( const char * filename, int wrap )
{
    //*
    //carrega a imagem
    int width, height;
    void * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return;

    // allocate buffer
    width = 256;
    height = 256;
    data = malloc( width * height * 3 );
    //data = new BYTE[width * height * 3];

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // build our texture MIP maps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width,
                       height, GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    // Set Texture mapping parameters
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
//*/
}
//---------------------------------------------------------------------------
// load a RGB .BMP file as a texture
void OpenTextures::loadTextureBMP( const char * szFileName, int wrap )
{
/*
  //carrega a imagem
  	HANDLE hFileHandle;
  	BITMAPINFO *pBitmapInfo = NULL;
  	unsigned long lInfoSize = 0;
  	unsigned long lBitSize = 0;
  	int nTextureWidth;
  	int nTextureHeight;
  	BYTE *pBitmapData;

  	// Open the Bitmap file
  	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,
  		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

  	// Check for open failure (most likely file does not exist).
  	if(hFileHandle == INVALID_HANDLE_VALUE)
  		return;

  	// File is Open. Read in bitmap header information
  	BITMAPFILEHEADER	bitmapHeader;
  	DWORD dwBytes;
  	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),
  		&dwBytes,NULL);

  		if(dwBytes != sizeof(BITMAPFILEHEADER))
  			return;

  		// Check format of bitmap file
  		if(bitmapHeader.bfType != 'MB')
  			return;

  		// Read in bitmap information structure
  		lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
  		pBitmapInfo = (BITMAPINFO *) new BYTE[lInfoSize];

  		ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);

  		if(dwBytes != lInfoSize)
  			return;

  		nTextureWidth = pBitmapInfo->bmiHeader.biWidth;
  		nTextureHeight = pBitmapInfo->bmiHeader.biHeight;
  		lBitSize = pBitmapInfo->bmiHeader.biSizeImage;

  		if(lBitSize == 0)
  			lBitSize = (nTextureWidth * pBitmapInfo->bmiHeader.biBitCount + 7) / 8 * abs(nTextureHeight);

  		// Allocate space for the actual bitmap
  		pBitmapData = new BYTE[lBitSize];

  		// Read in the bitmap bits
  		ReadFile(hFileHandle,pBitmapData,lBitSize,&dwBytes,NULL);

  		if(lBitSize != dwBytes)
  			{
  			if(pBitmapData)
  				delete [] (BYTE *) pBitmapData;
  			pBitmapData = NULL;

  			return;
  			}

  		CloseHandle(hFileHandle);

  		if(pBitmapInfo != NULL)
  			delete [] (BYTE *)pBitmapInfo;

  	// This is specific to the binary format of the data read in.
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
      glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
      glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

      glTexImage2D(GL_TEXTURE_2D, 0, 3, nTextureWidth, nTextureHeight, 0,
                   GL_BGR_EXT, GL_UNSIGNED_BYTE, pBitmapData);

  	if(pBitmapData)
  		delete [] (BYTE *) pBitmapData;

  // Set Texture mapping parameters
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
//*/
}
//---------------------------------------------------------------------------
void OpenTextures::read_JPEG_file ( char * filename, int wrap ) {
/*
	unsigned char * big_buff;
	struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;

	FILE * infile;
	JSAMPARRAY buffer;
	int row_stride;

	if ((infile = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", filename);
	}

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        fprintf(stderr, "jpeg error\n");
    }
    jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, infile);

	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;

	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	big_buff = (unsigned char *) malloc(cinfo.output_height * cinfo.output_width * cinfo.output_components);

	while (cinfo.output_scanline < cinfo.output_height)
	{
		JDIMENSION read_now = jpeg_read_scanlines(&cinfo, buffer, 1);
		memcpy(&big_buff[(cinfo.output_scanline - read_now) * cinfo.output_width * cinfo.output_components], buffer[0], row_stride);
	}

    //*
    //* We call gluBuild2DMipmaps to load the texture in opengl's memory and create mipmaps
    //*
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cinfo.output_width, cinfo.output_height, GL_RGB, GL_UNSIGNED_BYTE, big_buff);
    //*
    //* We no longer need the buffer since opengl has a copy now
    //*
	free(big_buff);

	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

  // Set Texture mapping parameters
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
//*/
}
//---------------------------------------------------------------------------
