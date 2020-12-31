#include "../headers/win32.h"
#include <stdlib.h>
#include <tchar.h>

#define BF_TYPE_BMP 0x4d42

#pragma pack(push, 1)
struct BITMAPFILEHEADER
{
	WORD bf_type;			/* Should be 0x4d42 for .bmp */
	DWORD bf_size;			/* Size in bytes of file */
	WORD bf_reserved1;		/* Must be 0 */
	WORD bf_reserved2;		/* Must be 0 */
	DWORD bf_offset_bits;	/* Offset in bytes from BITMAPFILEHEADER to
							bitmap bits */
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BITMAPINFOHEADER
{
	DWORD bi_size;			/* Number of bytes required by struct */
	LONG bi_width;			/* Width in pixels */
	LONG bi_height;			/* Height in pixels */
	WORD bi_planes;			/* Number of colour planes (must be 1) */
	WORD bi_bit_count;		/* Number of bits per pixel */
	DWORD bi_compression;	/* Type of compression */
	DWORD bi_size_image;	/* Size of image in bytes */
	LONG bi_x_pixels_per_meter;
	LONG bi_y_pixels_per_meter;
	DWORD bi_colours_used;
	DWORD bi_colours_important;
};
#pragma pack(pop)

static uint8* window_load_bmp(char* filename, struct BITMAPINFOHEADER* bm_info_header)
{
	FILE* pfile;
	//uint8* pbm_data;
	size_t num_read;
	struct BITMAPFILEHEADER bm_file_header;

	/* Read in binary mode */
	errno_t err = fopen_s(&pfile, filename, "rb");
	if (err != 0 || pfile == NULL)
	{
		/* Try get current working dir */
		TCHAR path_buffer[MAX_PATH] = { 0 };

		/* Get path to .exe directory*/
		if (GetCurrentDirectory(MAX_PATH, path_buffer) != 0)
		{
			_ftprintf(stderr, _T("Tried looking in: '%s'\n"), path_buffer);
		}

		LOG_ERROR("Error loading bmp '%s': Failed to open file\n", filename);

		return NULL;
	}

	/* Get file header */
	num_read = fread(&bm_file_header, sizeof(struct BITMAPFILEHEADER), 1, pfile);

	if (num_read == 0 || bm_file_header.bf_type != BF_TYPE_BMP)
	{
		LOG_ERROR("Error loading bmp '%s': Failed to read file header\n", filename);
		(void)fclose(pfile);
		return NULL;
	}

	num_read = fread(bm_info_header, sizeof(BITMAPINFOHEADER), sizeof(uint8), pfile);

	if (num_read == 0)
	{
		LOG_ERROR("Error loading bmp '%s': Failed to read file info header\n", filename);
		(void)fclose(pfile);
		return NULL;
	}

	(void)fseek(pfile, bm_file_header.bf_offset_bits, SEEK_SET);

	uint8* pbm_data = (uint8*)malloc(bm_info_header->bi_size_image);

	if (!pbm_data)
	{
		LOG_ERROR("Error loading bmp '%s': Failed to allocate memory for image\n", filename);
		(void)free(pbm_data);
		(void)fclose(pfile);
		return NULL;
	}

	num_read = fread(pbm_data, sizeof(uint8), bm_info_header->bi_size_image, pfile);  /* check args */

	if (num_read == 0 || pbm_data == NULL)
	{
		LOG_ERROR("Error loading bmp '%s': Failed to read image data\n", filename);
		(void)free(pbm_data);
		(void)fclose(pfile);
		return NULL;
	}

	/* Flip from BGR to RGB */
	uint8 swap_value;
	uint bytes_per_pixel = bm_info_header->bi_bit_count / 8;
	for (int i = 0; i < bm_info_header->bi_size_image; i += bytes_per_pixel)
	{
		swap_value = pbm_data[i];
		pbm_data[i] = pbm_data[i + 2];
		pbm_data[i + 2] = swap_value;
	}

	(void)fclose(pfile);

	return pbm_data;
}

struct Sprite_Image* window_sprite_image_load(char* filename)
{
	struct Sprite_Image* sprite_image;
	struct BITMAPINFOHEADER bm_info_header;

	sprite_image = malloc(sizeof(struct Sprite_Image));
	if (sprite_image == NULL)
	{
		LOG_ERROR("Error loading sprite from '%s': \
				Could not allocate memory -> malloc() failed\n",
			filename);
		return NULL;
	}

	sprite_image->pdata = window_load_bmp(filename, &bm_info_header);
	if (sprite_image->pdata == NULL)
	{
		LOG_ERROR("File '%s' could not be read\n", filename);
		return NULL;
	}

	sprite_image->bi_bit_count = bm_info_header.bi_bit_count;
	sprite_image->bi_size_image = bm_info_header.bi_size_image;
	sprite_image->bi_width = bm_info_header.bi_width;
	sprite_image->bi_height = bm_info_header.bi_height;

	return sprite_image;
}

void window_sprite_image_destroy(struct Sprite_Image* sprite_image)
{
	(void)free(sprite_image);
}

void window_sprite_destroy(struct Sprite* sprite)
{
	/* IDEA: free sprite->sprite_image if count = 0 ? */

	(void)free(sprite);
}
