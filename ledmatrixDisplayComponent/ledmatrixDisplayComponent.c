/**
 * Description: This file is migrated from https:github.com/Seeed-Studio/Seeed_RGB_LED_Matrix
 * 		Some functions have been renamed but its code still be the same
 * Author: tqkieu@tma.com.vn
 * 
 **/
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdio.h>
#include <errno.h>

#include "legato.h"
#include "interfaces.h"
#include "le_mutex.h"
#include "json.h"

#define LEDMATRIX_DATAHUB_STRING	"ledmatrix/string"
#define LEDMATRIX_DATAHUB_NUMBER	"ledmatrix/number"
#define LEDMATRIX_DATAHUB_EMOJI		"ledmatrix/emoji"

le_mutex_Ref_t ledmatrix_lock = NULL;

static void json_extract_dump(le_result_t res)
{
	if (res == LE_OK) {
		LE_INFO("json_Extract: successful");
	}
	if (res == LE_FORMAT_ERROR) {
		LE_ERROR("json_Extract: there's something wrong with the input JSON string.");
	}
	if (res == LE_BAD_PARAMETER) {
		LE_ERROR("json_Extract: there's something wrong with the extraction specification");
	}
	if (res == LE_NOT_FOUND) {
		LE_ERROR("json_Extract: the thing we are trying to extract doesn't exist in the JSON input");
	}
	if (res == LE_OVERFLOW) {
		LE_ERROR("json_Extract: the provided result buffer isn't big enough");
	}
	// LE_ASSERT_OK(res);
}
static void ledmatrixStringHandle(double timestamp,
				  const char* LE_NONNULL value,
				  void* contextPtr)
{
	char buffer[IO_MAX_STRING_VALUE_LEN];
	int duration;
	bool forever;
	int color;
	le_result_t le_res;
	json_DataType_t json_data_type;

	LE_INFO("ledmatrixStringHandle: timestamp %lf", timestamp);
	LE_INFO("ledmatrixStringHandle: value %s", value);

	// JSON message looks like this:
	// "
	// {
	// 	\"str\": \"Hello\",
	// 	\"duration\": 20000,
	// 	\"forever\": true,
	// 	\"color\": green
	// }
	// "
	if (!json_IsValid(value)) {
		LE_ERROR("INVALID JSON string");
		return;
	}

	// duration
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "duration", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for duration");
		return;
	}
	duration = (int)json_ConvertToNumber(buffer);
	
	// forever
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "forever", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_BOOLEAN) {
		LE_ERROR("WRONG data type for forever");
		return;
	}
	forever = json_ConvertToBoolean(buffer);

	// color
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "color", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for color");
		return;
	}
	color = (int)json_ConvertToNumber(buffer);

	// str
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "str", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_STRING) {
		LE_ERROR("WRONG data type for string");
		return;
	}

	le_mutex_Lock(ledmatrix_lock);
	ledmatrix_displayString(buffer, duration, forever, color);
	le_mutex_Unlock(ledmatrix_lock);
}
static void ledmatrixNumberHandle(double timestamp,
				  const char* LE_NONNULL value,
				  void* contextPtr)
{
	char buffer[IO_MAX_STRING_VALUE_LEN];
	int number;
	int duration;
	bool forever;
	int color;
	le_result_t le_res;
	json_DataType_t json_data_type;

	LE_INFO("ledmatrixNumberHandle: timestamp %lf", timestamp);
	LE_INFO("ledmatrixNumberHandle: value %s", value);

	// JSON message looks like this:
	// "
	// 	{
	// 		\"number\": number,
	// 		\"duration\": 1000,
	// 		\"forever\": true,
	// 		\"color\": red
	// 	}
	// ",
	if (!json_IsValid(value)) {
		LE_ERROR("INVALID JSON string");
		return;
	}

	// duration
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "duration", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for duration");
		return;
	}
	duration = (int)json_ConvertToNumber(buffer);
	
	// forever
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "forever", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_BOOLEAN) {
		LE_ERROR("WRONG data type for forever");
		return;
	}
	forever = json_ConvertToBoolean(buffer);

	// color
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "color", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for color");
		return;
	}
	color = (int)json_ConvertToNumber(buffer);

	// number
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "number", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for number");
		return;
	}
	number = (int) json_ConvertToNumber(buffer);

	le_mutex_Lock(ledmatrix_lock);
	ledmatrix_displayNumber(number, duration, forever, color);
	le_mutex_Unlock(ledmatrix_lock);
}
static void ledmatrixEmojiHandle(double timestamp,
				  const char* LE_NONNULL value,
				  void* contextPtr)
{
	char buffer[IO_MAX_STRING_VALUE_LEN];
	int emoji;
	int duration;
	bool forever;
	le_result_t le_res;
	json_DataType_t json_data_type;

	LE_INFO("ledmatrixEmojiHandle: timestamp %lf", timestamp);
	LE_INFO("ledmatrixEmojiHandle: value %s", value);

	// JSON message looks like this:
	// "
	// 	{
	// 		\"emoji\": emoji,
	// 		\"duration\": 1000,
	// 		\"forever\": true
	// 	}
	// "
	if (!json_IsValid(value)) {
		LE_ERROR("INVALID JSON string");
		return;
	}

	// duration
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "duration", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for duration");
		return;
	}
	duration = (int)json_ConvertToNumber(buffer);
	
	// forever
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "forever", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_BOOLEAN) {
		LE_ERROR("WRONG data type for forever");
		return;
	}
	forever = json_ConvertToBoolean(buffer);

	// emoji
	memset(buffer, 0, IO_MAX_STRING_VALUE_LEN);
	le_res = json_Extract(buffer,
			      IO_MAX_STRING_VALUE_LEN,
			      value,
			      "emoji", 
			      &json_data_type);
	json_extract_dump(le_res);
	if (json_data_type != JSON_TYPE_NUMBER) {
		LE_ERROR("WRONG data type for number");
		return;
	}
	emoji = (int) json_ConvertToNumber(buffer);

	le_mutex_Lock(ledmatrix_lock);
	ledmatrix_displayEmoji(emoji, duration, forever);
	le_mutex_Unlock(ledmatrix_lock);
}

COMPONENT_INIT
{
	LE_INFO("ledmatrixDisplay start");
	le_result_t result;
	ledmatrix_lock = le_mutex_CreateNonRecursive("ledmatrix");

	// LED matrix initialization
	ledmatrix_init("/dev/i2c-1", 0, 0);

	// This will be received from the Data Hub.
	result = io_CreateOutput(LEDMATRIX_DATAHUB_STRING,
				 IO_DATA_TYPE_JSON,
				 "string");
	LE_ASSERT(result == LE_OK);
	result = io_CreateOutput(LEDMATRIX_DATAHUB_NUMBER,
				 IO_DATA_TYPE_JSON,
				 "number");
	LE_ASSERT(result == LE_OK);
	result = io_CreateOutput(LEDMATRIX_DATAHUB_EMOJI,
				 IO_DATA_TYPE_JSON,
				 "emoji");
	LE_ASSERT(result == LE_OK);

	// Register for notification of updates to the counter value.
	io_AddJsonPushHandler(LEDMATRIX_DATAHUB_STRING,
			      ledmatrixStringHandle,
			      NULL);
	io_AddJsonPushHandler(LEDMATRIX_DATAHUB_NUMBER,
			      ledmatrixNumberHandle,
			      NULL);
	io_AddJsonPushHandler(LEDMATRIX_DATAHUB_EMOJI,
			      ledmatrixEmojiHandle,
			      NULL);
}