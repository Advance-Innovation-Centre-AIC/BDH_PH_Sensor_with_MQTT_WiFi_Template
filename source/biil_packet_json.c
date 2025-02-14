/*
 * bdh_json_packet.c
 *
 *  Created on: Feb 14, 2023
 *      Author: nipon
 */

#include "biil_packet_json.h"


void print_packet1_json(data_packet1_t *data, char *msg)
{
	cJSON *root;

	root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "dts", 1650946232574);
	cJSON_AddNumberToObject(root, "seq", data->seq);
	cJSON_AddStringToObject(root, "fw_version", FRIMWARE_VERSION);
	cJSON_AddNumberToObject(root, "user_input_bt1", data->user_bt1);
	cJSON_AddNumberToObject(root, "user_input_bt2", data->user_bt2);
//	cJSON_AddNumberToObject(root, "ph", data->ph_value);
//	cJSON_AddNumberToObject(root, "ph", (float)data->ph_value);
//	cJSON_AddNumberToObject(root, "ph", (double)data->ph_value + 0.000001);
//	double ph_value = (double)data->ph_value;
//	printf("ph_value = %.2f \r\n", data->ph_value);
//	cJSON_AddNumberToObject(root, "ph", ph_value);
	char ph_str[16];
	sprintf(ph_str, "%.2f", data->ph_value);  // Format as float string
	cJSON_AddRawToObject(root, "ph", ph_str);

//	char ph_str[16];
//	sprintf(ph_str, "%.2f", data->ph_value);  // fix ph to not convert float to int
//	cJSON_AddStringToObject(root, "ph", ph_str);
	cJSON_AddNumberToObject(root, "capsense_slider", data->capsense_slider);
	cJSON_AddNumberToObject(root, "capsense_bt1", data->capsense_bt1);
	cJSON_AddNumberToObject(root, "capsense_bt1", data->capsense_bt1);

	uint16_t len_str = strlen(cJSON_PrintUnformatted(root));

	strncpy(msg, cJSON_PrintUnformatted(root), len_str);
	msg[len_str] = '\0';
//		printf(msg);
//		printf("\r\n");
//		printf("ph_value = %.2f \r\n", data->ph_value);

	cJSON_Delete(root);
}

void print_packet2_json(data_packet2_t *data, char *msg)
{
	cJSON *root;

	root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "dts", 1650946232574);
	cJSON_AddNumberToObject(root, "seq", data->seq);
	cJSON_AddStringToObject(root, "fw_version", FRIMWARE_VERSION);
	cJSON *xensiv;
			cJSON_AddItemToObject(root, "xensiv", xensiv = cJSON_CreateObject());
	cJSON_AddNumberToObject(xensiv, "pressure", data->pressure);
	cJSON_AddNumberToObject(xensiv, "temperature", data->temperature);
	cJSON *orientation9axis;
			cJSON_AddItemToObject(root, "orientation9axis", orientation9axis = cJSON_CreateObject());
	cJSON_AddNumberToObject(orientation9axis, "accel_x", data->bmx160_data.accel.x);
	cJSON_AddNumberToObject(orientation9axis, "accel_y", data->bmx160_data.accel.y);
	cJSON_AddNumberToObject(orientation9axis, "accel_z", data->bmx160_data.accel.z);
	cJSON_AddNumberToObject(orientation9axis, "gyro_x", data->bmx160_data.gyro.x);
	cJSON_AddNumberToObject(orientation9axis, "gyro_y", data->bmx160_data.gyro.y);
	cJSON_AddNumberToObject(orientation9axis, "gyro_z", data->bmx160_data.gyro.z);
	cJSON_AddNumberToObject(orientation9axis, "mag_x", data->bmx160_data.mag.x);
	cJSON_AddNumberToObject(orientation9axis, "mag_y", data->bmx160_data.mag.y);
	cJSON_AddNumberToObject(orientation9axis, "mag_z", data->bmx160_data.mag.z);
	cJSON *mic;
			cJSON_AddItemToObject(root, "mic", mic = cJSON_CreateObject());
	cJSON_AddNumberToObject(mic, "analog_mic", data->analog_mic);
	cJSON_AddNumberToObject(mic, "digital_mic", data->digital_mic);

	uint16_t len_str = strlen(cJSON_PrintUnformatted(root));

	strncpy(msg, cJSON_PrintUnformatted(root), len_str);
	msg[len_str] = '\0';

	cJSON_Delete(root);
//	printf(msg);
//	printf("\r\n");
}

