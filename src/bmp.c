/*
 * bmp.c -- bmp texture loader
 * last modification: dec. 15, 2005
 *
 * Copyright (c) 2005 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../include/bmp.h"

void ReadBMP1bit(FILE *fp, GLubyte *colormap, os_type_e os_type, gl_texture_t *texinfo)
{
  int i, j, cmPixSize;
  GLubyte color, clrIndex;

  cmPixSize = (os_type == BMP_OS2) ? 3 : 4;

  for (i = 0; i < texinfo->width * texinfo->height; )
    {
      /* read index color byte */
      color = (GLubyte)fgetc( fp );

      /* convert 8-by-8 pixels to RGB 24 bits */
      for (j = 7; j >= 0; --j, ++i)
	{
	  clrIndex = ((color & (1 << j)) > 0);
	  texinfo->texels[(i * 3) + 2] = colormap[(clrIndex * cmPixSize) + 0];
	  texinfo->texels[(i * 3) + 1] = colormap[(clrIndex * cmPixSize) + 1];
	  texinfo->texels[(i * 3) + 0] = colormap[(clrIndex * cmPixSize) + 2];
	}
    }
}

void ReadBMP4bits(FILE *fp, GLubyte *colormap, os_type_e os_type, gl_texture_t *texinfo)
{
  int i, cmPixSize;
  GLubyte color, clrIndex;

  cmPixSize = (os_type == BMP_OS2) ? 3 : 4;

  for (i = 0; i < texinfo->width * texinfo->height; i += 2)
    {
      /* read index color byte */
      color = (GLubyte)fgetc (fp);

      /* convert 2-by-2 pixels to RGB 24 bits */

      /* first pixel */
      clrIndex = (color >> 4);
      texinfo->texels[(i * 3) + 2] = colormap[(clrIndex * cmPixSize) + 0];
      texinfo->texels[(i * 3) + 1] = colormap[(clrIndex * cmPixSize) + 1];
      texinfo->texels[(i * 3) + 0] = colormap[(clrIndex * cmPixSize) + 2];

      /* second pixel */
      clrIndex = (color & 0x0F);
      texinfo->texels[(i * 3) + 5] = colormap[(clrIndex * cmPixSize) + 0];
      texinfo->texels[(i * 3) + 4] = colormap[(clrIndex * cmPixSize) + 1];
      texinfo->texels[(i * 3) + 3] = colormap[(clrIndex * cmPixSize) + 2];
    }
}

void ReadBMP8bits(FILE *fp, GLubyte *colormap, os_type_e os_type, gl_texture_t *texinfo)
{
  int i, cmPixSize;
  GLubyte color;

  cmPixSize = (os_type == BMP_OS2) ? 3 : 4;

  for (i = 0; i < texinfo->width * texinfo->height; ++i)
    {
      /* read index color byte */
      color = (GLubyte)fgetc (fp);

      /* convert to RGB 24 bits */
      texinfo->texels[(i * 3) + 2] = colormap[(color * cmPixSize) + 0];
      texinfo->texels[(i * 3) + 1] = colormap[(color * cmPixSize) + 1];
      texinfo->texels[(i * 3) + 0] = colormap[(color * cmPixSize) + 2];
    }
}

void ReadBMP24bits (FILE *fp, gl_texture_t *texinfo)
{
  int i;

  for (i = 0; i < texinfo->width * texinfo->height; ++i)
    {
      /* read and convert BGR to RGB */
      texinfo->texels[(i * 3) + 2] = (GLubyte)fgetc (fp);
      texinfo->texels[(i * 3) + 1] = (GLubyte)fgetc (fp);
      texinfo->texels[(i * 3) + 0] = (GLubyte)fgetc (fp);
    }
}

void ReadBMP32bits (FILE *fp, gl_texture_t *texinfo)
{
  int i;
  GLubyte skip;

  for (i = 0; i < texinfo->width * texinfo->height; ++i)
    {
      /* read and convert BGRA to RGB */
      texinfo->texels[(i * 3) + 2] = (GLubyte)fgetc (fp);
      texinfo->texels[(i * 3) + 1] = (GLubyte)fgetc (fp);
      texinfo->texels[(i * 3) + 0] = (GLubyte)fgetc (fp);

      /* skip last byte */
      skip = (GLubyte)fgetc (fp);
    }
}

void ReadBMP8bitsRLE (FILE *fp, GLubyte *colormap, gl_texture_t *texinfo)
{
  int i;
  GLubyte color, skip;
  GLubyte byte1, byte2;
  GLubyte *ptr = texinfo->texels;

  while (ptr < texinfo->texels + (texinfo->width * texinfo->height) * 3)
    {
      /* read first two byte */
      byte1 = (GLubyte)fgetc (fp);
      byte2 = (GLubyte)fgetc (fp);

      if (byte1 == RLE_COMMAND)
	{
	  for (i = 0; i < byte2; ++i, ptr += 3)
	    {
	      color = (GLubyte)fgetc (fp);

	      ptr[0] = colormap[(color * 4) + 2];
	      ptr[1] = colormap[(color * 4) + 1];
	      ptr[2] = colormap[(color * 4) + 0];
	    }

	  if (byte2 % 2)
	    {
	      /* skip one byte if number of pixels is odd */
	      skip = (GLubyte)fgetc (fp);
	    }
	}
      else
	{
	  for (i = 0; i < byte1; ++i, ptr += 3)
	    {
	      ptr[0] = colormap[(byte2 * 4) + 2];
	      ptr[1] = colormap[(byte2 * 4) + 1];
	      ptr[2] = colormap[(byte2 * 4) + 0];
	    }
	}
    }
}

void ReadBMP4bitsRLE (FILE *fp, GLubyte *colormap, gl_texture_t *texinfo)
{
  int i, bytesRead = 0;
  GLubyte color, databyte, skip;
  GLubyte byte1, byte2;
  GLubyte *ptr = texinfo->texels;

  while (ptr < texinfo->texels + (texinfo->width * texinfo->height) * 3)
    {
      /* read first two byte */
      byte1 = (GLubyte)fgetc (fp);
      byte2 = (GLubyte)fgetc (fp);
      bytesRead += 2;

      if (byte1 == RLE_COMMAND)
	{
	  databyte = 0;

	  for (i = 0; i < byte2; ++i, ptr += 3)
	    {
	      if (i % 2)
		{
		  /* four less significant bits */
		  color = (databyte & 0x0F);
		}
	      else
		{
		  databyte = (GLubyte)fgetc (fp);
		  ++bytesRead;

		  /* four most significant bits */
		  color = (databyte >> 4);
		}

	      /* convert from index color to RGB 24 bits */
	      ptr[0] = colormap[(color * 4) + 2];
	      ptr[1] = colormap[(color * 4) + 1];
	      ptr[2] = colormap[(color * 4) + 0];
	    }

	  if (bytesRead % 2)
	    {
	      /* skip one byte if number of read bytes is odd */
	      skip = (GLubyte)fgetc (fp);
	      ++bytesRead;
	    }
	}
      else
	{
	  for (i = 0; i < byte1; ++i, ptr += 3)
	    {
	      if (i % 2)
		color = (byte2 & 0x0F);
	      else
		color = (byte2 >> 4);

	      /* convert from index color to RGB 24 bits */
	      ptr[0] = colormap[(color * 4) + 2];
	      ptr[1] = colormap[(color * 4) + 1];
	      ptr[2] = colormap[(color * 4) + 0];
	    }
	}
    }
}

gl_texture_t * ReadBMPFile (const char *filename)
{
  FILE *fp;
  gl_texture_t *texinfo;
  bmp_file_header_t bmfh;
  bmp_info_header_t bmih;
  bmp_core_header_t bmch;
  os_type_e os_type;
  unsigned int compression;
  unsigned int bitCount;
  fpos_t bmhPos;
  GLubyte *colormap = NULL;
  int colormapSize;

  fp = fopen (filename, "rb");
  if (!fp)
    {
      fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
      return NULL;
    }

  /* read bitmap file header */
  fread (&bmfh, sizeof (bmp_file_header_t), 1, fp);
  fgetpos (fp, &bmhPos);

  if (strncmp ((char *)bmfh.bfType, "BM", 2) != 0)
    {
      fprintf (stderr, "%s is not a valid BMP file!\n", filename);
      fclose (fp);
      return NULL;
    }

  /* allocate memory for texture info and init some parameters */
  texinfo = (gl_texture_t *)malloc (sizeof (gl_texture_t));
  texinfo->format = GL_RGB;
  texinfo->internalFormat = 3;

  /* read bitmap info header */
  fread (&bmih, sizeof (bmp_info_header_t), 1, fp);

  if (bmih.biCompression > 3)
    {
      /* this is an OS/2 bitmap file, we don't use
	 bitmap info header but bitmap core header instead */

      /* we must go back to read bitmap core header */
      fsetpos (fp, &bmhPos);
      fread (&bmch, sizeof (bmp_core_header_t), 1, fp);

      os_type = BMP_OS2;
      compression = BI_RGB;
      bitCount = bmch.bcBitCount;


      texinfo->width = bmch.bcWidth;
      texinfo->height = bmch.bcHeight;
    }
  else
    {
      /* Windows style */
      compression = bmih.biCompression;
      os_type = BMP_WIN;
      bitCount = bmih.biBitCount;

      texinfo->width = bmih.biWidth;
      texinfo->height = bmih.biHeight;
    }

  /* look for palette data if present */
  if (bitCount <= 8)
    {
      colormapSize = (1 << bitCount) * ((os_type == BMP_OS2) ? 3 : 4);
      colormap = (GLubyte *)malloc (colormapSize * sizeof (GLubyte));

      fread (colormap, sizeof (GLubyte), colormapSize, fp);
    }

  /* memory allocation for pixel data */
  texinfo->texels = (GLubyte *)malloc (texinfo->width
	       * texinfo->height * texinfo->internalFormat);

  /* go to begining of pixel data */
  fseek (fp, bmfh.bfOffBits, SEEK_SET);

  /* read image data */
  switch (compression)
    {
    case BI_RGB:
      switch (bitCount)
	{
	case 1:
	  ReadBMP1bit (fp, colormap, os_type, texinfo);
	  break;

	case 4:
	  ReadBMP4bits (fp, colormap, os_type, texinfo);
	  break;

	case 8:
	  ReadBMP8bits (fp, colormap, os_type, texinfo);
	  break;

	case 24:
	  ReadBMP24bits (fp, texinfo);
	  break;

	case 32:
	  ReadBMP32bits (fp, texinfo);
	  break;
	}

      break;

    case BI_RLE8:
      ReadBMP8bitsRLE (fp, colormap, texinfo);
      break;

    case BI_RLE4:
      ReadBMP4bitsRLE (fp, colormap, texinfo);
      break;

    case BI_BITFIELDS:
    default:
      /* unsupported file types */
      fprintf (stderr, "unsupported bitmap type or bad file"
	       "compression type (%i)\n", compression);
      free (texinfo->texels);
      free (texinfo);
      texinfo = NULL;
      break;
    }

  /* no longer need colormap data */
  if (colormap)
    free (colormap);

  fclose (fp);
  return texinfo;
}

GLuint loadBMPTexture (const char *filename)
{
  gl_texture_t *bmp_tex = NULL;
  GLuint tex_id = 0;

  bmp_tex = ReadBMPFile (filename);

  if (bmp_tex && bmp_tex->texels)
    {
      /* generate texture */
      glGenTextures (1, &bmp_tex->id);
      glBindTexture (GL_TEXTURE_2D, bmp_tex->id);

      /* setup some parameters for texture filters and mipmapping */
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      /*
      glTexImage2D (GL_TEXTURE_2D, 0, bmp_tex->internalFormat,
		    bmp_tex->width, bmp_tex->height, 0, bmp_tex->format,
		    GL_UNSIGNED_BYTE, bmp_tex->texels);
      */

      gluBuild2DMipmaps (GL_TEXTURE_2D, bmp_tex->internalFormat,
			 bmp_tex->width, bmp_tex->height,
			 bmp_tex->format, GL_UNSIGNED_BYTE, bmp_tex->texels);

      tex_id = bmp_tex->id;

      /* OpenGL has its own copy of texture data */
      free (bmp_tex->texels);
      free (bmp_tex);
    }

  return tex_id;
}
