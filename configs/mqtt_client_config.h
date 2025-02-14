/******************************************************************************
* File Name:   mqtt_client_config.h
*
* Description: This file contains all the configuration macros used by the
*              MQTT client in this example.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2020-2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#ifndef MQTT_CLIENT_CONFIG_H_
#define MQTT_CLIENT_CONFIG_H_

#include "cy_mqtt_api.h"

/*******************************************************************************
* Macros
********************************************************************************/

/***************** MQTT CLIENT CONNECTION CONFIGURATION MACROS *****************/
/* MQTT Broker/Server address and port used for the MQTT connection. */
#define MQTT_BROKER_ADDRESS             "mqtt.thailand-smartliving.com"
#define MQTT_PORT                        8883

/* Set this macro to 1 if a secure (TLS) connection to the MQTT Broker is  
 * required to be established, else 0.
 */
#define MQTT_SECURE_CONNECTION            ( 1 )

/* Configure the user credentials to be sent as part of MQTT CONNECT packet */
#define MQTT_USERNAME                    "Group00015"
#define MQTT_PASSWORD                    "12341234"


/********************* MQTT MESSAGE CONFIGURATION MACROS **********************/
/* The MQTT topics to be used by the publisher and subscriber. */
#define MQTT_PUB_CY8CKIT_62S2_40312_TOPIC 	"biil/CY8CKIT-62S2-40312/Group00015"
#define MQTT_PUB_CY8CKIT_028_SENSE_TOPIC 	"biil/CY8CKIT-028-SENSE/Group0015"
#define MQTT_PUB_TOPIC                    "ledstatus"
#define MQTT_SUB_TOPIC                    "ledstatus"

/* Set the QoS that is associated with the MQTT publish, and subscribe messages.
 * Valid choices are 0, 1, and 2. Other values should not be used in this macro.
 */
#define MQTT_MESSAGES_QOS                 ( 0 )

/* Configuration for the 'Last Will and Testament (LWT)'. It is an MQTT message 
 * that will be published by the MQTT broker if the MQTT connection is 
 * unexpectedly closed. This configuration is sent to the MQTT broker during 
 * MQTT connect operation and the MQTT broker will publish the Will message on 
 * the Will topic when it recognizes an unexpected disconnection from the client.
 * 
 * If you want to use the last will message, set this macro to 1 and configure
 * the topic and will message, else 0.
 */
#define ENABLE_LWT_MESSAGE                ( 0 )
#if ENABLE_LWT_MESSAGE
    #define MQTT_WILL_TOPIC_NAME          MQTT_PUB_TOPIC "/will"
    #define MQTT_WILL_MESSAGE             ("MQTT client unexpectedly disconnected!")
#endif

/* MQTT messages which are published on the MQTT_PUB_TOPIC that controls the
 * device (user LED in this example) state in this code example.
 */
#define MQTT_DEVICE_ON_MESSAGE            "TURN ON"
#define MQTT_DEVICE_OFF_MESSAGE           "TURN OFF"


/******************* OTHER MQTT CLIENT CONFIGURATION MACROS *******************/
/* A unique client identifier to be used for every MQTT connection. */
#define MQTT_CLIENT_IDENTIFIER            "Group00015"  				//"psoc6-mqtt-client"

/* The timeout in milliseconds for MQTT operations in this example. */
#define MQTT_TIMEOUT_MS                   ( 5000 )

/* The keep-alive interval in seconds used for MQTT ping request. */
#define MQTT_KEEP_ALIVE_SECONDS           ( 60 )

/* Every active MQTT connection must have a unique client identifier. If you 
 * are using the above 'MQTT_CLIENT_IDENTIFIER' as client ID for multiple MQTT 
 * connections simultaneously, set this macro to 1. The device will then
 * generate a unique client identifier by appending a timestamp to the 
 * 'MQTT_CLIENT_IDENTIFIER' string. Example: 'psoc6-mqtt-client5927'
 */
#define GENERATE_UNIQUE_CLIENT_ID         ( 0 )

/* The longest client identifier that an MQTT server must accept (as defined
 * by the MQTT 3.1.1 spec) is 23 characters. However some MQTT brokers support 
 * longer client IDs. Configure this macro as per the MQTT broker specification. 
 */
#define MQTT_CLIENT_IDENTIFIER_MAX_LEN    ( 23 )

/* As per Internet Assigned Numbers Authority (IANA) the port numbers assigned 
 * for MQTT protocol are 1883 for non-secure connections and 8883 for secure
 * connections. In some cases there is a need to use other ports for MQTT like
 * port 443 (which is reserved for HTTPS). Application Layer Protocol 
 * Negotiation (ALPN) is an extension to TLS that allows many protocols to be 
 * used over a secure connection. The ALPN ProtocolNameList specifies the 
 * protocols that the client would like to use to communicate over TLS.
 * 
 * This macro specifies the ALPN Protocol Name to be used that is supported
 * by the MQTT broker in use.
 * Note: For AWS IoT, currently "x-amzn-mqtt-ca" is the only supported ALPN 
 *       ProtocolName and it is only supported on port 443.
 * 
 * Uncomment the below line and specify the ALPN Protocol Name to use this 
 * feature.
 */
// #define MQTT_ALPN_PROTOCOL_NAME          "x-amzn-mqtt-ca"

/* Server Name Indication (SNI) is extension to the Transport Layer Security 
 * (TLS) protocol. As required by some MQTT Brokers, SNI typically includes the 
 * hostname in the Client Hello message sent during TLS handshake.
 * 
 * Uncomment the below line and specify the SNI Host Name to use this extension
 * as specified by the MQTT Broker.
 */
// #define MQTT_SNI_HOSTNAME                 "SNI_HOST_NAME"

/* A Network buffer is allocated for sending and receiving MQTT packets over 
 * the network. Specify the size of this buffer using this macro.
 * 
 * Note: The minimum buffer size is defined by 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE' 
 * macro in the MQTT library. Please ensure this macro value is larger than 
 * 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE'.
 */
#define MQTT_NETWORK_BUFFER_SIZE          ( 2 * CY_MQTT_MIN_NETWORK_BUFFER_SIZE )

/* Maximum MQTT connection re-connection limit. */
#define MAX_MQTT_CONN_RETRIES            (150u)

/* MQTT re-connection time interval in milliseconds. */
#define MQTT_CONN_RETRY_INTERVAL_MS      (2000)


/**************** MQTT CLIENT CERTIFICATE CONFIGURATION MACROS ****************/

/* Configure the below credentials in case of a secure MQTT connection. */
/* PEM-encoded client certificate */
#define CLIENT_CERTIFICATE      \
"-----BEGIN CERTIFICATE-----\n"\
"MIIC8TCCAdkCCQCm3BeClQPi4jANBgkqhkiG9w0BAQsFADAlMSMwIQYDVQQDDBoq\n"\
"LnRoYWlsYW5kLXNtYXJ0bGl2aW5nLmNvbTAeFw0yMzAzMDcxMDU5MTNaFw0yNDAz\n"\
"MDYxMDU5MTNaMFAxDTALBgNVBAMMBEJpaWwxDDAKBgNVBAoMA0JVVTERMA8GA1UE\n"\
"CwwIRUFTVFBhcmsxCzAJBgNVBAYTAlRIMREwDwYDVQQHDAhCYW5nc2FlbjCCASIw\n"\
"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAN7/vi0GIpnQkVCtACzA+qg1IvUc\n"\
"8bG+QKEXFie4r/8qAEbSHY8ZQub4UBxDNiFo6oO0GA558L7v4vriZjLxKoBi2UZt\n"\
"RiTHKUt/V9Cb1gLBPqIDYW/VU6WLFnCxgf2bRvsnzqo2jxhkaLEsBxXT+wKKF0Ol\n"\
"7BP90kCuJBSaqNxaplUixeYXw+PJEcBuq9qzeaIoqWUIOErikZtX8gA1/OK/yr5S\n"\
"DmfEN/Fdf0jMf1JtMRLb5NcNP8ibKC0+0jMSNVo/UlW1QdlUCJ2yW9Ckaj+PrSWe\n"\
"Wyl+Ajr4R2yGDnaLTaRQQGEk7CTYJbHJByhBXFB5LmKIv8p4hMWOWDUQ+csCAwEA\n"\
"ATANBgkqhkiG9w0BAQsFAAOCAQEAgfMas3BuEa29PUNMSankBoXKjVcRrONmiz0Z\n"\
"EDYuMJ58lMDSInp+EpJMC95ASVnlxwge7uDwnkRovLVXDqdHq97XPlcrT3SmwEhy\n"\
"0tQPUdJg02WSr1gKD3JvmTYcEhgVlD29CBl2rotrM4NO5bSIS3mj9jb1kxNCsSvT\n"\
"UwMEzW700ijrUlvab9UvXgbOjSzpu4tEzv508znDPCdi1TlA17Ul4HqvSSteCCq/\n"\
"fWQr3PYCLq8hap2uII6ElEaRpxH6y0I0ypHEkZddG+/Z71xkP7vJZ9aC5dwfXSdO\n"\
"mXEB5Q9TO9NaqZ8zcP3lJ89EDMFiHW1nxJ7QbhJqk1SgE47TZw==\n"\
"-----END CERTIFICATE-----\n"


/* PEM-encoded client private key */
#define CLIENT_PRIVATE_KEY          \
"-----BEGIN PRIVATE KEY-----\n"\
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDe/74tBiKZ0JFQ\n"\
"rQAswPqoNSL1HPGxvkChFxYnuK//KgBG0h2PGULm+FAcQzYhaOqDtBgOefC+7+L6\n"\
"4mYy8SqAYtlGbUYkxylLf1fQm9YCwT6iA2Fv1VOlixZwsYH9m0b7J86qNo8YZGix\n"\
"LAcV0/sCihdDpewT/dJAriQUmqjcWqZVIsXmF8PjyRHAbqvas3miKKllCDhK4pGb\n"\
"V/IANfziv8q+Ug5nxDfxXX9IzH9SbTES2+TXDT/ImygtPtIzEjVaP1JVtUHZVAid\n"\
"slvQpGo/j60lnlspfgI6+Edshg52i02kUEBhJOwk2CWxyQcoQVxQeS5iiL/KeITF\n"\
"jlg1EPnLAgMBAAECggEANt4b774Ls2bS6lO2sExHIC36zO5zNXWHN1uT0vApNZIj\n"\
"AUnfhf8ELAo6w8lxvySuVvtv09gC+SfS5EHiPXSDLZWkuiRW1uO98FqDw8skDAd6\n"\
"HqjQR5DohNnFCrNSNZEIFPHFcrH74VeLPtSDZcaDgytw7+8aOA0Ct3FhZURsedLK\n"\
"cABnaL+7NLuA+wnEeT2D+dOi7LWnRdCja8VBteKLOZJDnrKUEfpMk/BJ9qGiRu1/\n"\
"b7z+G/XypaxeQcvqu3yQnLaWcn6wzpnM6YolER5k/0CGTlV414zJ7J/ECvX+LNGv\n"\
"s+KWF/DDSwHjYVVKu6cx8DerOdOCGVf1bZWxJS0qcQKBgQDpS0KuP+WPhhEqpdea\n"\
"LX28y1JGQ986PKgfGf4KB7TYnYQJEc8hkG7PmYr6+soiwE13Fm38RfgHSNeEdH52\n"\
"kuWtFM5ZaPvcytnmQHAmLGCLisUFPrZVD8MJOpWdhAAQHVdGSohYe5KCdNc87FW3\n"\
"HP9NfwgxYv9gwY5Uk8PnDQXrAwKBgQD0s/kXK6Wz9DIGd1duFyqSy1FRnONkdsny\n"\
"SNJtyXnOJDgygUcr9IYPAVUI4t5jW1br5XdDB1ujCGiPaeiYWEhosIWDaNMPt/WT\n"\
"30AKcGAINiwoPtzcOCeSmE62gJU3aOABOrkP6WZ69tbZAMCcmUkdATPXxu1X6Kt3\n"\
"R0jyLrjXmQKBgHnV1iMON6L2zyxIpApey5W3UWZkt8XAO8TSXDt8vtOJn5Tk+hl7\n"\
"RoOgmlZsdvgjGdGhoxrmp5uWTQddl1XxbYUwontLOo2aWqXG7UriTiFR/Ya5s5tE\n"\
"ugSt1ckHUMkZqaSJ9B7RmjgLMQUeH72bpTEhsHOqUdiD/QLqkJqv0HFlAoGBANdH\n"\
"0rgAzVpBVxV7Pu768JiOyS8M4L0NCOPgD0lJPKEQGmTMeYoBKUPgPyh/N3mf7RvC\n"\
"GCdfPM504lBxs5D78lAwJHYU7cLha+s5OMU2UjZHOpf5niMcQCxnVLCY9S33VUOf\n"\
"nxqRk3hQ23m0gMAE117uJOcL+tkhOGDK1TFDy5jZAoGADcgwU0HgGSzpNPLy0CEf\n"\
"iPEZGRGdMXM1woJk7FdKg1MdzzkJCYJqjpGugyDD6FmPs6FydeORyfYoOzcyOGl7\n"\
"SXn/7kgRmNoRJXbB7qufanOy21GXXhxQmZZpxmaaZ/ZO00dS61yI7pAvCk1UR0u9\n"\
"+qYB96Rqsz2niPeokgkMAzQ=\n"\
"-----END PRIVATE KEY-----\n"

/* PEM-encoded Root CA certificate */
#define ROOT_CA_CERTIFICATE     \
"-----BEGIN CERTIFICATE-----\n"\
"MIIEMjCCAxqgAwIBAgIBATANBgkqhkiG9w0BAQUFADB7MQswCQYDVQQGEwJHQjEb\n"\
"MBkGA1UECAwSR3JlYXRlciBNYW5jaGVzdGVyMRAwDgYDVQQHDAdTYWxmb3JkMRow\n"\
"GAYDVQQKDBFDb21vZG8gQ0EgTGltaXRlZDEhMB8GA1UEAwwYQUFBIENlcnRpZmlj\n"\
"YXRlIFNlcnZpY2VzMB4XDTA0MDEwMTAwMDAwMFoXDTI4MTIzMTIzNTk1OVowezEL\n"\
"MAkGA1UEBhMCR0IxGzAZBgNVBAgMEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UE\n"\
"BwwHU2FsZm9yZDEaMBgGA1UECgwRQ29tb2RvIENBIExpbWl0ZWQxITAfBgNVBAMM\n"\
"GEFBQSBDZXJ0aWZpY2F0ZSBTZXJ2aWNlczCCASIwDQYJKoZIhvcNAQEBBQADggEP\n"\
"ADCCAQoCggEBAL5AnfRu4ep2hxxNRUSOvkbIgwadwSr+GB+O5AL686tdUIoWMQua\n"\
"BtDFcCLNSS1UY8y2bmhGC1Pqy0wkwLxyTurxFa70VJoSCsN6sjNg4tqJVfMiWPPe\n"\
"3M/vg4aijJRPn2jymJBGhCfHdr/jzDUsi14HZGWCwEiwqJH5YZ92IFCokcdmtet4\n"\
"YgNW8IoaE+oxox6gmf049vYnMlhvB/VruPsUK6+3qszWY19zjNoFmag4qMsXeDZR\n"\
"rOme9Hg6jc8P2ULimAyrL58OAd7vn5lJ8S3frHRNG5i1R8XlKdH5kBjHYpy+g8cm\n"\
"ez6KJcfA3Z3mNWgQIJ2P2N7Sw4ScDV7oL8kCAwEAAaOBwDCBvTAdBgNVHQ4EFgQU\n"\
"oBEKIz6W8Qfs4q8p74Klf9AwpLQwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQF\n"\
"MAMBAf8wewYDVR0fBHQwcjA4oDagNIYyaHR0cDovL2NybC5jb21vZG9jYS5jb20v\n"\
"QUFBQ2VydGlmaWNhdGVTZXJ2aWNlcy5jcmwwNqA0oDKGMGh0dHA6Ly9jcmwuY29t\n"\
"b2RvLm5ldC9BQUFDZXJ0aWZpY2F0ZVNlcnZpY2VzLmNybDANBgkqhkiG9w0BAQUF\n"\
"AAOCAQEACFb8AvCb6P+k+tZ7xkSAzk/ExfYAWMymtrwUSWgEdujm7l3sAg9g1o1Q\n"\
"GE8mTgHj5rCl7r+8dFRBv/38ErjHT1r0iWAFf2C3BUrz9vHCv8S5dIa2LX1rzNLz\n"\
"Rt0vxuBqw8M0Ayx9lt1awg6nCpnBBYurDC/zXDrPbDdVCYfeU0BsWO/8tqtlbgT2\n"\
"G9w84FoVxp7Z8VlIMCFlA2zs6SFz7JsDoeA3raAVGI/6ugLOpyypEBMs1OUIJqsi\n"\
"l2D4kF501KKaU73yqWjgom7C12yxow+ev+to51byrvLjKzg6CYG1a4XXvi3tPxq3\n"\
"smPi9WIsgtRqAEFQ8TmDn5XpNpaYbg==\n"\
"-----END CERTIFICATE-----\n"


/******************************************************************************
* Global Variables
*******************************************************************************/
extern cy_mqtt_broker_info_t broker_info;
extern cy_awsport_ssl_credentials_t  *security_info;
extern cy_mqtt_connect_info_t connection_info;


#endif /* MQTT_CLIENT_CONFIG_H_ */
