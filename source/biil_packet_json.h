/*
 * bdh_json_packet.h
 *
 *  Created on: Feb 14, 2023
 *      Author: nipon
 */

#ifndef SOURCE_BIIL_PACKET_JSON_H_
#define SOURCE_BIIL_PACKET_JSON_H_

#include "common.h"
#include <string.h>
#include "cJSON.h"

//#define TOPIC_MQTT_SIZE 	256
#define PAYLOAD_MQTT_SIZE	320

void print_packet1_json(data_packet1_t *data, char *msg);
void print_packet2_json(data_packet2_t *data, char *msg);

#endif /* SOURCE_BIIL_PACKET_JSON_H_ */
