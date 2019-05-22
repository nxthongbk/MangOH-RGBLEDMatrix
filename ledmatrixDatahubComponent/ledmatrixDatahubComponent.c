#include "legato.h"
#include "interfaces.h"

#define LEDMATRIX_DATAHUB_STRING	"ledmatrix/string"
#define LEDMATRIX_DATAHUB_NUMBER	"ledmatrix/number"
#define LEDMATRIX_DATAHUB_EMOJI		"ledmatrix/emoji"

// copy defined color's code of ledmatrix
enum ledmatrix_color
{
	RED = 0x00,
	ORANGE = 0x12,
	YELLOW = 0x18,
	GREEN = 0x52,
	CYAN = 0x7f,
	BLUE = 0xaa,
	PURPLE =0xc3,
	PINK = 0xdc,
	WHITE = 0xfe,
	BLACK = 0xff,
};

COMPONENT_INIT
{
	le_result_t result;
	LE_INFO(" ledmatrixDatahub start");
	// This will be provided to the Data Hub. --> send to ledmatrix
	result = io_CreateInput(LEDMATRIX_DATAHUB_STRING,
				IO_DATA_TYPE_JSON,
				"string");
	LE_ASSERT(result == LE_OK);
	result = io_CreateInput(LEDMATRIX_DATAHUB_NUMBER,
				IO_DATA_TYPE_JSON,
				"number");
	LE_ASSERT(result == LE_OK);
	result = io_CreateInput(LEDMATRIX_DATAHUB_EMOJI,
				IO_DATA_TYPE_JSON,
				"emoji");
	LE_ASSERT(result == LE_OK);

	result = admin_SetSource("/app/ledmatrixDisplay/" LEDMATRIX_DATAHUB_STRING,
				 "/app/ledmatrixDatahub/" LEDMATRIX_DATAHUB_STRING);
	LE_ASSERT(result == LE_OK);
	result = admin_SetSource("/app/ledmatrixDisplay/" LEDMATRIX_DATAHUB_NUMBER,
				 "/app/ledmatrixDatahub/" LEDMATRIX_DATAHUB_NUMBER);
	LE_ASSERT(result == LE_OK);
	result = admin_SetSource("/app/ledmatrixDisplay/" LEDMATRIX_DATAHUB_EMOJI,
				 "/app/ledmatrixDatahub/" LEDMATRIX_DATAHUB_EMOJI);
	LE_ASSERT(result == LE_OK);

	char json_str[IO_MAX_STRING_VALUE_LEN];
	// display numbers
	for (int i = 0; i < 10; i++) {
		LE_INFO("Display number: %d", i);
		memset(json_str, 0 , IO_MAX_STRING_VALUE_LEN);
		sprintf(json_str,
			"{\"number\":%d,\"duration\":1000,\"forever\":true,\"color\":%d}",
			i,
			RED);
		io_PushJson(LEDMATRIX_DATAHUB_NUMBER, IO_NOW, (const char *)json_str);
		sleep(1);
	}

	// display emoji
	for (int i = 0; i < 35; i++) {
		LE_INFO("Display emoji: %d", i);
		memset(json_str, 0 , IO_MAX_STRING_VALUE_LEN);
		sprintf(json_str,
			"{\"emoji\":%d,\"duration\":1000,\"forever\":true}",
			i);
		io_PushJson(LEDMATRIX_DATAHUB_EMOJI, IO_NOW, (const char *)json_str);
		sleep(1);
	}

	// display string
	memset(json_str, 0 , IO_MAX_STRING_VALUE_LEN);
	sprintf(json_str,
		"{\"str\":\"%s\",\"duration\":20000,\"forever\":true,\"color\":%d}",
		"Hello RGB LED matrix",
		GREEN);
	LE_INFO("Display string: %s", "Hello RGB LED matrix");
	io_PushJson(LEDMATRIX_DATAHUB_STRING, IO_NOW, (const char *)json_str);
}
