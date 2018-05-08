// ©2018 Yuichiro Nakada
// clang -Os mp4parser.c -o mp4parser -lm

#include <stdio.h>
//#define NDEBUG
#include "mp4parser.h"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("Invalid argument, useage:\n mp4parser /path/to/mp4file\n");
		return -1;
	}

	stream_t *s = create_file_stream();
	if (stream_open(s, argv[1], MODE_READ) == 0) {
		printf("Can not open file\n");
		return -1;
	}

	MP4_Box_t *SearchResult = MP4_BoxGetRoot(s);
	printf("search result box is %c%c%c%c\n", SearchResult->i_type&0x000000ff,
		(SearchResult->i_type&0x0000ff00)>>8,
		(SearchResult->i_type&0x00ff0000)>>16,
		(SearchResult->i_type&0xff000000)>>24);

	MP4_Box_t *p_ftyp = MP4_BoxGet(SearchResult, "ftyp");
	printf("ftyp.major_brand is %s\n", (char*)&p_ftyp->data.p_ftyp->i_major_brand);
	MP4_BoxFree(s, SearchResult);

	stream_close(s);
	destory_file_stream(s);

	return 0;
}
