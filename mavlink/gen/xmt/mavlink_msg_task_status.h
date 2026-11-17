#pragma once
// MESSAGE TASK_STATUS PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TASK_STATUS 13001


typedef struct __mavlink_task_status_t {
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 int32_t lat; /*< [degree] latitude of target, [-180,180], LSB：180/(2^31-1)*/
 int32_t lon; /*< [degree] longitude of target, [-90,90], LSB：90 /(2^31-1)*/
 uint16_t atitude; /*< [m] atitude of target, [-500,3000], LSB：0.1，offset： -500*/
 uint8_t sin_Y_mode; /*< [m/s] Y-信模式*/
 uint8_t trigC; /*< [m/s] trigger condition*/
} mavlink_task_status_t;

#define MAVLINK_MSG_ID_TASK_STATUS_LEN 16
#define MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN 16
#define MAVLINK_MSG_ID_13001_LEN 16
#define MAVLINK_MSG_ID_13001_MIN_LEN 16

#define MAVLINK_MSG_ID_TASK_STATUS_CRC 122
#define MAVLINK_MSG_ID_13001_CRC 122



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TASK_STATUS { \
    13001, \
    "TASK_STATUS", \
    6, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_task_status_t, time_boot_ms) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_task_status_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_task_status_t, lon) }, \
         { "atitude", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_task_status_t, atitude) }, \
         { "sin_Y_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_task_status_t, sin_Y_mode) }, \
         { "trigC", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_task_status_t, trigC) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TASK_STATUS { \
    "TASK_STATUS", \
    6, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_task_status_t, time_boot_ms) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_task_status_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_task_status_t, lon) }, \
         { "atitude", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_task_status_t, atitude) }, \
         { "sin_Y_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_task_status_t, sin_Y_mode) }, \
         { "trigC", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_task_status_t, trigC) }, \
         } \
}
#endif

/**
 * @brief Pack a task_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of target, [-180,180], LSB：180/(2^31-1)
 * @param lon [degree] longitude of target, [-90,90], LSB：90 /(2^31-1)
 * @param atitude [m] atitude of target, [-500,3000], LSB：0.1，offset： -500
 * @param sin_Y_mode [m/s] Y-信模式
 * @param trigC [m/s] trigger condition
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_task_status_pack(uint32_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, uint8_t sin_Y_mode, uint8_t trigC)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TASK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint16_t(buf, 12, atitude);
    _mav_put_uint8_t(buf, 14, sin_Y_mode);
    _mav_put_uint8_t(buf, 15, trigC);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TASK_STATUS_LEN);
#else
    mavlink_task_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.atitude = atitude;
    packet.sin_Y_mode = sin_Y_mode;
    packet.trigC = trigC;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TASK_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TASK_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
}

/**
 * @brief Pack a task_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of target, [-180,180], LSB：180/(2^31-1)
 * @param lon [degree] longitude of target, [-90,90], LSB：90 /(2^31-1)
 * @param atitude [m] atitude of target, [-500,3000], LSB：0.1，offset： -500
 * @param sin_Y_mode [m/s] Y-信模式
 * @param trigC [m/s] trigger condition
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_task_status_pack_status(uint32_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, uint8_t sin_Y_mode, uint8_t trigC)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TASK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint16_t(buf, 12, atitude);
    _mav_put_uint8_t(buf, 14, sin_Y_mode);
    _mav_put_uint8_t(buf, 15, trigC);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TASK_STATUS_LEN);
#else
    mavlink_task_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.atitude = atitude;
    packet.sin_Y_mode = sin_Y_mode;
    packet.trigC = trigC;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TASK_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TASK_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, 0);
#endif
}

/**
 * @brief Pack a task_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of target, [-180,180], LSB：180/(2^31-1)
 * @param lon [degree] longitude of target, [-90,90], LSB：90 /(2^31-1)
 * @param atitude [m] atitude of target, [-500,3000], LSB：0.1，offset： -500
 * @param sin_Y_mode [m/s] Y-信模式
 * @param trigC [m/s] trigger condition
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_task_status_pack_chan(uint32_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,int32_t lat,int32_t lon,uint16_t atitude,uint8_t sin_Y_mode,uint8_t trigC)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TASK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint16_t(buf, 12, atitude);
    _mav_put_uint8_t(buf, 14, sin_Y_mode);
    _mav_put_uint8_t(buf, 15, trigC);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TASK_STATUS_LEN);
#else
    mavlink_task_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.atitude = atitude;
    packet.sin_Y_mode = sin_Y_mode;
    packet.trigC = trigC;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TASK_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TASK_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
}

/**
 * @brief Encode a task_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param task_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_task_status_encode(uint32_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_task_status_t* task_status)
{
    return mavlink_msg_task_status_pack(system_id, component_id, msg, task_status->time_boot_ms, task_status->lat, task_status->lon, task_status->atitude, task_status->sin_Y_mode, task_status->trigC);
}

/**
 * @brief Encode a task_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param task_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_task_status_encode_chan(uint32_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_task_status_t* task_status)
{
    return mavlink_msg_task_status_pack_chan(system_id, component_id, chan, msg, task_status->time_boot_ms, task_status->lat, task_status->lon, task_status->atitude, task_status->sin_Y_mode, task_status->trigC);
}

/**
 * @brief Encode a task_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param task_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_task_status_encode_status(uint32_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_task_status_t* task_status)
{
    return mavlink_msg_task_status_pack_status(system_id, component_id, _status, msg,  task_status->time_boot_ms, task_status->lat, task_status->lon, task_status->atitude, task_status->sin_Y_mode, task_status->trigC);
}

/**
 * @brief Send a task_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of target, [-180,180], LSB：180/(2^31-1)
 * @param lon [degree] longitude of target, [-90,90], LSB：90 /(2^31-1)
 * @param atitude [m] atitude of target, [-500,3000], LSB：0.1，offset： -500
 * @param sin_Y_mode [m/s] Y-信模式
 * @param trigC [m/s] trigger condition
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_task_status_send(mavlink_channel_t chan, uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, uint8_t sin_Y_mode, uint8_t trigC)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TASK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint16_t(buf, 12, atitude);
    _mav_put_uint8_t(buf, 14, sin_Y_mode);
    _mav_put_uint8_t(buf, 15, trigC);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TASK_STATUS, buf, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
#else
    mavlink_task_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.atitude = atitude;
    packet.sin_Y_mode = sin_Y_mode;
    packet.trigC = trigC;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TASK_STATUS, (const char *)&packet, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
#endif
}

/**
 * @brief Send a task_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_task_status_send_struct(mavlink_channel_t chan, const mavlink_task_status_t* task_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_task_status_send(chan, task_status->time_boot_ms, task_status->lat, task_status->lon, task_status->atitude, task_status->sin_Y_mode, task_status->trigC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TASK_STATUS, (const char *)task_status, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_TASK_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_task_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, uint8_t sin_Y_mode, uint8_t trigC)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint16_t(buf, 12, atitude);
    _mav_put_uint8_t(buf, 14, sin_Y_mode);
    _mav_put_uint8_t(buf, 15, trigC);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TASK_STATUS, buf, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
#else
    mavlink_task_status_t *packet = (mavlink_task_status_t *)msgbuf;
    packet->time_boot_ms = time_boot_ms;
    packet->lat = lat;
    packet->lon = lon;
    packet->atitude = atitude;
    packet->sin_Y_mode = sin_Y_mode;
    packet->trigC = trigC;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TASK_STATUS, (const char *)packet, MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN, MAVLINK_MSG_ID_TASK_STATUS_LEN, MAVLINK_MSG_ID_TASK_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE TASK_STATUS UNPACKING


/**
 * @brief Get field time_boot_ms from task_status message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_task_status_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field lat from task_status message
 *
 * @return [degree] latitude of target, [-180,180], LSB：180/(2^31-1)
 */
static inline int32_t mavlink_msg_task_status_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field lon from task_status message
 *
 * @return [degree] longitude of target, [-90,90], LSB：90 /(2^31-1)
 */
static inline int32_t mavlink_msg_task_status_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field atitude from task_status message
 *
 * @return [m] atitude of target, [-500,3000], LSB：0.1，offset： -500
 */
static inline uint16_t mavlink_msg_task_status_get_atitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field sin_Y_mode from task_status message
 *
 * @return [m/s] Y-信模式
 */
static inline uint8_t mavlink_msg_task_status_get_sin_Y_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field trigC from task_status message
 *
 * @return [m/s] trigger condition
 */
static inline uint8_t mavlink_msg_task_status_get_trigC(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  15);
}

/**
 * @brief Decode a task_status message into a struct
 *
 * @param msg The message to decode
 * @param task_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_task_status_decode(const mavlink_message_t* msg, mavlink_task_status_t* task_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    task_status->time_boot_ms = mavlink_msg_task_status_get_time_boot_ms(msg);
    task_status->lat = mavlink_msg_task_status_get_lat(msg);
    task_status->lon = mavlink_msg_task_status_get_lon(msg);
    task_status->atitude = mavlink_msg_task_status_get_atitude(msg);
    task_status->sin_Y_mode = mavlink_msg_task_status_get_sin_Y_mode(msg);
    task_status->trigC = mavlink_msg_task_status_get_trigC(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TASK_STATUS_LEN? msg->len : MAVLINK_MSG_ID_TASK_STATUS_LEN;
        memset(task_status, 0, MAVLINK_MSG_ID_TASK_STATUS_LEN);
    memcpy(task_status, _MAV_PAYLOAD(msg), len);
#endif

}
