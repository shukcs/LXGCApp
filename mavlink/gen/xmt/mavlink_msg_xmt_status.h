#pragma once
// MESSAGE XMT_STATUS PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_XMT_STATUS 13000


typedef struct __mavlink_xmt_status_t {
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 int32_t lat; /*< [degree] latitude of vehicle, [-180,180], LSB：10e-7)*/
 int32_t lon; /*< [degree] longitude of vehicle, [-90,90], LSB：10e-7*/
 uint32_t target_dis; /*< [m] distance between target and vehicle, LSB: 0.01*/
 uint32_t sys_stat; /*< [m] system status*/
 uint32_t sys_data; /*< [m] system data*/
 uint16_t atitude; /*< [m] atitude of vehicle, [-500,5000], LSB：0.1，offset： -500*/
 int16_t speed_N; /*< [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)*/
 int16_t speed_E; /*< [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)*/
 int16_t speed_G; /*< [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)*/
 int16_t yaw; /*< [degree] Yaw of vehicle, [-180,180], LSB：180/(2^15-1)*/
 int16_t pitch; /*< [degree] Pitch of vehicle, [-90,90], LSB：180/(2^15-1)*/
 int16_t campass; /*< [degree] Campass of vehicle, [-180,180], LSB：180/(2^15-1)*/
 int16_t acc_N; /*< [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)*/
 int16_t acc_E; /*< [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)*/
 int16_t acc_G; /*< [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)*/
 int16_t angu_vel_X; /*< [degree/s] X-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)*/
 int16_t angu_vel_Y; /*< [degree/s] Y-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)*/
 int16_t angu_vel_Z; /*< [degree/s] Z-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)*/
 int16_t ctrl_rudder_1; /*< [degree] rudder 1 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t ctrl_rudder_2; /*< [degree] rudder 2 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t ctrl_rudder_3; /*< [degree] rudder 3 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t ctrl_rudder_4; /*< [degree] rudder 4 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t fdbk_rudder_1; /*< [degree] rudder 1 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t fdbk_rudder_2; /*< [degree] rudder 2 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t fdbk_rudder_3; /*< [degree] rudder 3 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t fdbk_rudder_4; /*< [degree] rudder 4 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t attack_angu; /*< [degree] Attack angular, [-30,30]，LSB：30/(2^15-1)*/
 int16_t side_slip_angu; /*< [degree] side slip angular, [-30,30]，LSB: 30/(2^15-1)*/
 int16_t throttle; /*< [degree] throttle, [0,1]，LSB: 0.0001*/
} mavlink_xmt_status_t;

#define MAVLINK_MSG_ID_XMT_STATUS_LEN 72
#define MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN 72
#define MAVLINK_MSG_ID_13000_LEN 72
#define MAVLINK_MSG_ID_13000_MIN_LEN 72

#define MAVLINK_MSG_ID_XMT_STATUS_CRC 9
#define MAVLINK_MSG_ID_13000_CRC 9



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_XMT_STATUS { \
    13000, \
    "XMT_STATUS", \
    30, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_xmt_status_t, time_boot_ms) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_xmt_status_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_xmt_status_t, lon) }, \
         { "atitude", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_xmt_status_t, atitude) }, \
         { "speed_N", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_xmt_status_t, speed_N) }, \
         { "speed_E", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_xmt_status_t, speed_E) }, \
         { "speed_G", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_xmt_status_t, speed_G) }, \
         { "yaw", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_xmt_status_t, yaw) }, \
         { "pitch", NULL, MAVLINK_TYPE_INT16_T, 0, 34, offsetof(mavlink_xmt_status_t, pitch) }, \
         { "campass", NULL, MAVLINK_TYPE_INT16_T, 0, 36, offsetof(mavlink_xmt_status_t, campass) }, \
         { "acc_N", NULL, MAVLINK_TYPE_INT16_T, 0, 38, offsetof(mavlink_xmt_status_t, acc_N) }, \
         { "acc_E", NULL, MAVLINK_TYPE_INT16_T, 0, 40, offsetof(mavlink_xmt_status_t, acc_E) }, \
         { "acc_G", NULL, MAVLINK_TYPE_INT16_T, 0, 42, offsetof(mavlink_xmt_status_t, acc_G) }, \
         { "angu_vel_X", NULL, MAVLINK_TYPE_INT16_T, 0, 44, offsetof(mavlink_xmt_status_t, angu_vel_X) }, \
         { "angu_vel_Y", NULL, MAVLINK_TYPE_INT16_T, 0, 46, offsetof(mavlink_xmt_status_t, angu_vel_Y) }, \
         { "angu_vel_Z", NULL, MAVLINK_TYPE_INT16_T, 0, 48, offsetof(mavlink_xmt_status_t, angu_vel_Z) }, \
         { "ctrl_rudder_1", NULL, MAVLINK_TYPE_INT16_T, 0, 50, offsetof(mavlink_xmt_status_t, ctrl_rudder_1) }, \
         { "ctrl_rudder_2", NULL, MAVLINK_TYPE_INT16_T, 0, 52, offsetof(mavlink_xmt_status_t, ctrl_rudder_2) }, \
         { "ctrl_rudder_3", NULL, MAVLINK_TYPE_INT16_T, 0, 54, offsetof(mavlink_xmt_status_t, ctrl_rudder_3) }, \
         { "ctrl_rudder_4", NULL, MAVLINK_TYPE_INT16_T, 0, 56, offsetof(mavlink_xmt_status_t, ctrl_rudder_4) }, \
         { "fdbk_rudder_1", NULL, MAVLINK_TYPE_INT16_T, 0, 58, offsetof(mavlink_xmt_status_t, fdbk_rudder_1) }, \
         { "fdbk_rudder_2", NULL, MAVLINK_TYPE_INT16_T, 0, 60, offsetof(mavlink_xmt_status_t, fdbk_rudder_2) }, \
         { "fdbk_rudder_3", NULL, MAVLINK_TYPE_INT16_T, 0, 62, offsetof(mavlink_xmt_status_t, fdbk_rudder_3) }, \
         { "fdbk_rudder_4", NULL, MAVLINK_TYPE_INT16_T, 0, 64, offsetof(mavlink_xmt_status_t, fdbk_rudder_4) }, \
         { "attack_angu", NULL, MAVLINK_TYPE_INT16_T, 0, 66, offsetof(mavlink_xmt_status_t, attack_angu) }, \
         { "side_slip_angu", NULL, MAVLINK_TYPE_INT16_T, 0, 68, offsetof(mavlink_xmt_status_t, side_slip_angu) }, \
         { "throttle", NULL, MAVLINK_TYPE_INT16_T, 0, 70, offsetof(mavlink_xmt_status_t, throttle) }, \
         { "target_dis", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_xmt_status_t, target_dis) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_xmt_status_t, sys_stat) }, \
         { "sys_data", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_xmt_status_t, sys_data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_XMT_STATUS { \
    "XMT_STATUS", \
    30, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_xmt_status_t, time_boot_ms) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_xmt_status_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_xmt_status_t, lon) }, \
         { "atitude", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_xmt_status_t, atitude) }, \
         { "speed_N", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_xmt_status_t, speed_N) }, \
         { "speed_E", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_xmt_status_t, speed_E) }, \
         { "speed_G", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_xmt_status_t, speed_G) }, \
         { "yaw", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_xmt_status_t, yaw) }, \
         { "pitch", NULL, MAVLINK_TYPE_INT16_T, 0, 34, offsetof(mavlink_xmt_status_t, pitch) }, \
         { "campass", NULL, MAVLINK_TYPE_INT16_T, 0, 36, offsetof(mavlink_xmt_status_t, campass) }, \
         { "acc_N", NULL, MAVLINK_TYPE_INT16_T, 0, 38, offsetof(mavlink_xmt_status_t, acc_N) }, \
         { "acc_E", NULL, MAVLINK_TYPE_INT16_T, 0, 40, offsetof(mavlink_xmt_status_t, acc_E) }, \
         { "acc_G", NULL, MAVLINK_TYPE_INT16_T, 0, 42, offsetof(mavlink_xmt_status_t, acc_G) }, \
         { "angu_vel_X", NULL, MAVLINK_TYPE_INT16_T, 0, 44, offsetof(mavlink_xmt_status_t, angu_vel_X) }, \
         { "angu_vel_Y", NULL, MAVLINK_TYPE_INT16_T, 0, 46, offsetof(mavlink_xmt_status_t, angu_vel_Y) }, \
         { "angu_vel_Z", NULL, MAVLINK_TYPE_INT16_T, 0, 48, offsetof(mavlink_xmt_status_t, angu_vel_Z) }, \
         { "ctrl_rudder_1", NULL, MAVLINK_TYPE_INT16_T, 0, 50, offsetof(mavlink_xmt_status_t, ctrl_rudder_1) }, \
         { "ctrl_rudder_2", NULL, MAVLINK_TYPE_INT16_T, 0, 52, offsetof(mavlink_xmt_status_t, ctrl_rudder_2) }, \
         { "ctrl_rudder_3", NULL, MAVLINK_TYPE_INT16_T, 0, 54, offsetof(mavlink_xmt_status_t, ctrl_rudder_3) }, \
         { "ctrl_rudder_4", NULL, MAVLINK_TYPE_INT16_T, 0, 56, offsetof(mavlink_xmt_status_t, ctrl_rudder_4) }, \
         { "fdbk_rudder_1", NULL, MAVLINK_TYPE_INT16_T, 0, 58, offsetof(mavlink_xmt_status_t, fdbk_rudder_1) }, \
         { "fdbk_rudder_2", NULL, MAVLINK_TYPE_INT16_T, 0, 60, offsetof(mavlink_xmt_status_t, fdbk_rudder_2) }, \
         { "fdbk_rudder_3", NULL, MAVLINK_TYPE_INT16_T, 0, 62, offsetof(mavlink_xmt_status_t, fdbk_rudder_3) }, \
         { "fdbk_rudder_4", NULL, MAVLINK_TYPE_INT16_T, 0, 64, offsetof(mavlink_xmt_status_t, fdbk_rudder_4) }, \
         { "attack_angu", NULL, MAVLINK_TYPE_INT16_T, 0, 66, offsetof(mavlink_xmt_status_t, attack_angu) }, \
         { "side_slip_angu", NULL, MAVLINK_TYPE_INT16_T, 0, 68, offsetof(mavlink_xmt_status_t, side_slip_angu) }, \
         { "throttle", NULL, MAVLINK_TYPE_INT16_T, 0, 70, offsetof(mavlink_xmt_status_t, throttle) }, \
         { "target_dis", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_xmt_status_t, target_dis) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_xmt_status_t, sys_stat) }, \
         { "sys_data", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_xmt_status_t, sys_data) }, \
         } \
}
#endif

/**
 * @brief Pack a xmt_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of vehicle, [-180,180], LSB：10e-7)
 * @param lon [degree] longitude of vehicle, [-90,90], LSB：10e-7
 * @param atitude [m] atitude of vehicle, [-500,5000], LSB：0.1，offset： -500
 * @param speed_N [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_E [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_G [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param yaw [degree] Yaw of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param pitch [degree] Pitch of vehicle, [-90,90], LSB：180/(2^15-1)
 * @param campass [degree] Campass of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param acc_N [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_E [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_G [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param angu_vel_X [degree/s] X-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Y [degree/s] Y-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Z [degree/s] Z-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param ctrl_rudder_1 [degree] rudder 1 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_2 [degree] rudder 2 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_3 [degree] rudder 3 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_4 [degree] rudder 4 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_1 [degree] rudder 1 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_2 [degree] rudder 2 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_3 [degree] rudder 3 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_4 [degree] rudder 4 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param attack_angu [degree] Attack angular, [-30,30]，LSB：30/(2^15-1)
 * @param side_slip_angu [degree] side slip angular, [-30,30]，LSB: 30/(2^15-1)
 * @param throttle [degree] throttle, [0,1]，LSB: 0.0001
 * @param target_dis [m] distance between target and vehicle, LSB: 0.01
 * @param sys_stat [m] system status
 * @param sys_data [m] system data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_xmt_status_pack(uint32_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, int16_t speed_N, int16_t speed_E, int16_t speed_G, int16_t yaw, int16_t pitch, int16_t campass, int16_t acc_N, int16_t acc_E, int16_t acc_G, int16_t angu_vel_X, int16_t angu_vel_Y, int16_t angu_vel_Z, int16_t ctrl_rudder_1, int16_t ctrl_rudder_2, int16_t ctrl_rudder_3, int16_t ctrl_rudder_4, int16_t fdbk_rudder_1, int16_t fdbk_rudder_2, int16_t fdbk_rudder_3, int16_t fdbk_rudder_4, int16_t attack_angu, int16_t side_slip_angu, int16_t throttle, uint32_t target_dis, uint32_t sys_stat, uint32_t sys_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_XMT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint32_t(buf, 12, target_dis);
    _mav_put_uint32_t(buf, 16, sys_stat);
    _mav_put_uint32_t(buf, 20, sys_data);
    _mav_put_uint16_t(buf, 24, atitude);
    _mav_put_int16_t(buf, 26, speed_N);
    _mav_put_int16_t(buf, 28, speed_E);
    _mav_put_int16_t(buf, 30, speed_G);
    _mav_put_int16_t(buf, 32, yaw);
    _mav_put_int16_t(buf, 34, pitch);
    _mav_put_int16_t(buf, 36, campass);
    _mav_put_int16_t(buf, 38, acc_N);
    _mav_put_int16_t(buf, 40, acc_E);
    _mav_put_int16_t(buf, 42, acc_G);
    _mav_put_int16_t(buf, 44, angu_vel_X);
    _mav_put_int16_t(buf, 46, angu_vel_Y);
    _mav_put_int16_t(buf, 48, angu_vel_Z);
    _mav_put_int16_t(buf, 50, ctrl_rudder_1);
    _mav_put_int16_t(buf, 52, ctrl_rudder_2);
    _mav_put_int16_t(buf, 54, ctrl_rudder_3);
    _mav_put_int16_t(buf, 56, ctrl_rudder_4);
    _mav_put_int16_t(buf, 58, fdbk_rudder_1);
    _mav_put_int16_t(buf, 60, fdbk_rudder_2);
    _mav_put_int16_t(buf, 62, fdbk_rudder_3);
    _mav_put_int16_t(buf, 64, fdbk_rudder_4);
    _mav_put_int16_t(buf, 66, attack_angu);
    _mav_put_int16_t(buf, 68, side_slip_angu);
    _mav_put_int16_t(buf, 70, throttle);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_XMT_STATUS_LEN);
#else
    mavlink_xmt_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.target_dis = target_dis;
    packet.sys_stat = sys_stat;
    packet.sys_data = sys_data;
    packet.atitude = atitude;
    packet.speed_N = speed_N;
    packet.speed_E = speed_E;
    packet.speed_G = speed_G;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.campass = campass;
    packet.acc_N = acc_N;
    packet.acc_E = acc_E;
    packet.acc_G = acc_G;
    packet.angu_vel_X = angu_vel_X;
    packet.angu_vel_Y = angu_vel_Y;
    packet.angu_vel_Z = angu_vel_Z;
    packet.ctrl_rudder_1 = ctrl_rudder_1;
    packet.ctrl_rudder_2 = ctrl_rudder_2;
    packet.ctrl_rudder_3 = ctrl_rudder_3;
    packet.ctrl_rudder_4 = ctrl_rudder_4;
    packet.fdbk_rudder_1 = fdbk_rudder_1;
    packet.fdbk_rudder_2 = fdbk_rudder_2;
    packet.fdbk_rudder_3 = fdbk_rudder_3;
    packet.fdbk_rudder_4 = fdbk_rudder_4;
    packet.attack_angu = attack_angu;
    packet.side_slip_angu = side_slip_angu;
    packet.throttle = throttle;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_XMT_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_XMT_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
}

/**
 * @brief Pack a xmt_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of vehicle, [-180,180], LSB：10e-7)
 * @param lon [degree] longitude of vehicle, [-90,90], LSB：10e-7
 * @param atitude [m] atitude of vehicle, [-500,5000], LSB：0.1，offset： -500
 * @param speed_N [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_E [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_G [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param yaw [degree] Yaw of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param pitch [degree] Pitch of vehicle, [-90,90], LSB：180/(2^15-1)
 * @param campass [degree] Campass of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param acc_N [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_E [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_G [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param angu_vel_X [degree/s] X-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Y [degree/s] Y-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Z [degree/s] Z-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param ctrl_rudder_1 [degree] rudder 1 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_2 [degree] rudder 2 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_3 [degree] rudder 3 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_4 [degree] rudder 4 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_1 [degree] rudder 1 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_2 [degree] rudder 2 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_3 [degree] rudder 3 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_4 [degree] rudder 4 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param attack_angu [degree] Attack angular, [-30,30]，LSB：30/(2^15-1)
 * @param side_slip_angu [degree] side slip angular, [-30,30]，LSB: 30/(2^15-1)
 * @param throttle [degree] throttle, [0,1]，LSB: 0.0001
 * @param target_dis [m] distance between target and vehicle, LSB: 0.01
 * @param sys_stat [m] system status
 * @param sys_data [m] system data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_xmt_status_pack_status(uint32_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
            uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, int16_t speed_N, int16_t speed_E, int16_t speed_G, int16_t yaw, int16_t pitch,
            int16_t campass, int16_t acc_N, int16_t acc_E, int16_t acc_G, int16_t angu_vel_X, int16_t angu_vel_Y, int16_t angu_vel_Z, int16_t ctrl_rudder_1,
            int16_t ctrl_rudder_2, int16_t ctrl_rudder_3, int16_t ctrl_rudder_4, int16_t fdbk_rudder_1, int16_t fdbk_rudder_2, int16_t fdbk_rudder_3,
            int16_t fdbk_rudder_4, int16_t attack_angu, int16_t side_slip_angu, int16_t throttle, uint32_t target_dis, uint32_t sys_stat, uint32_t sys_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_XMT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint32_t(buf, 12, target_dis);
    _mav_put_uint32_t(buf, 16, sys_stat);
    _mav_put_uint32_t(buf, 20, sys_data);
    _mav_put_uint16_t(buf, 24, atitude);
    _mav_put_int16_t(buf, 26, speed_N);
    _mav_put_int16_t(buf, 28, speed_E);
    _mav_put_int16_t(buf, 30, speed_G);
    _mav_put_int16_t(buf, 32, yaw);
    _mav_put_int16_t(buf, 34, pitch);
    _mav_put_int16_t(buf, 36, campass);
    _mav_put_int16_t(buf, 38, acc_N);
    _mav_put_int16_t(buf, 40, acc_E);
    _mav_put_int16_t(buf, 42, acc_G);
    _mav_put_int16_t(buf, 44, angu_vel_X);
    _mav_put_int16_t(buf, 46, angu_vel_Y);
    _mav_put_int16_t(buf, 48, angu_vel_Z);
    _mav_put_int16_t(buf, 50, ctrl_rudder_1);
    _mav_put_int16_t(buf, 52, ctrl_rudder_2);
    _mav_put_int16_t(buf, 54, ctrl_rudder_3);
    _mav_put_int16_t(buf, 56, ctrl_rudder_4);
    _mav_put_int16_t(buf, 58, fdbk_rudder_1);
    _mav_put_int16_t(buf, 60, fdbk_rudder_2);
    _mav_put_int16_t(buf, 62, fdbk_rudder_3);
    _mav_put_int16_t(buf, 64, fdbk_rudder_4);
    _mav_put_int16_t(buf, 66, attack_angu);
    _mav_put_int16_t(buf, 68, side_slip_angu);
    _mav_put_int16_t(buf, 70, throttle);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_XMT_STATUS_LEN);
#else
    mavlink_xmt_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.target_dis = target_dis;
    packet.sys_stat = sys_stat;
    packet.sys_data = sys_data;
    packet.atitude = atitude;
    packet.speed_N = speed_N;
    packet.speed_E = speed_E;
    packet.speed_G = speed_G;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.campass = campass;
    packet.acc_N = acc_N;
    packet.acc_E = acc_E;
    packet.acc_G = acc_G;
    packet.angu_vel_X = angu_vel_X;
    packet.angu_vel_Y = angu_vel_Y;
    packet.angu_vel_Z = angu_vel_Z;
    packet.ctrl_rudder_1 = ctrl_rudder_1;
    packet.ctrl_rudder_2 = ctrl_rudder_2;
    packet.ctrl_rudder_3 = ctrl_rudder_3;
    packet.ctrl_rudder_4 = ctrl_rudder_4;
    packet.fdbk_rudder_1 = fdbk_rudder_1;
    packet.fdbk_rudder_2 = fdbk_rudder_2;
    packet.fdbk_rudder_3 = fdbk_rudder_3;
    packet.fdbk_rudder_4 = fdbk_rudder_4;
    packet.attack_angu = attack_angu;
    packet.side_slip_angu = side_slip_angu;
    packet.throttle = throttle;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_XMT_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_XMT_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, 0);
#endif
}

/**
 * @brief Pack a xmt_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of vehicle, [-180,180], LSB：10e-7)
 * @param lon [degree] longitude of vehicle, [-90,90], LSB：10e-7
 * @param atitude [m] atitude of vehicle, [-500,5000], LSB：0.1，offset： -500
 * @param speed_N [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_E [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_G [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param yaw [degree] Yaw of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param pitch [degree] Pitch of vehicle, [-90,90], LSB：180/(2^15-1)
 * @param campass [degree] Campass of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param acc_N [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_E [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_G [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param angu_vel_X [degree/s] X-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Y [degree/s] Y-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Z [degree/s] Z-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param ctrl_rudder_1 [degree] rudder 1 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_2 [degree] rudder 2 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_3 [degree] rudder 3 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_4 [degree] rudder 4 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_1 [degree] rudder 1 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_2 [degree] rudder 2 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_3 [degree] rudder 3 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_4 [degree] rudder 4 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param attack_angu [degree] Attack angular, [-30,30]，LSB：30/(2^15-1)
 * @param side_slip_angu [degree] side slip angular, [-30,30]，LSB: 30/(2^15-1)
 * @param throttle [degree] throttle, [0,1]，LSB: 0.0001
 * @param target_dis [m] distance between target and vehicle, LSB: 0.01
 * @param sys_stat [m] system status
 * @param sys_data [m] system data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_xmt_status_pack_chan(uint32_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,int32_t lat,int32_t lon,uint16_t atitude,int16_t speed_N,int16_t speed_E,int16_t speed_G,int16_t yaw,int16_t pitch,int16_t campass,int16_t acc_N,int16_t acc_E,int16_t acc_G,int16_t angu_vel_X,int16_t angu_vel_Y,int16_t angu_vel_Z,int16_t ctrl_rudder_1,int16_t ctrl_rudder_2,int16_t ctrl_rudder_3,int16_t ctrl_rudder_4,int16_t fdbk_rudder_1,int16_t fdbk_rudder_2,int16_t fdbk_rudder_3,int16_t fdbk_rudder_4,int16_t attack_angu,int16_t side_slip_angu,int16_t throttle,uint32_t target_dis,uint32_t sys_stat,uint32_t sys_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_XMT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint32_t(buf, 12, target_dis);
    _mav_put_uint32_t(buf, 16, sys_stat);
    _mav_put_uint32_t(buf, 20, sys_data);
    _mav_put_uint16_t(buf, 24, atitude);
    _mav_put_int16_t(buf, 26, speed_N);
    _mav_put_int16_t(buf, 28, speed_E);
    _mav_put_int16_t(buf, 30, speed_G);
    _mav_put_int16_t(buf, 32, yaw);
    _mav_put_int16_t(buf, 34, pitch);
    _mav_put_int16_t(buf, 36, campass);
    _mav_put_int16_t(buf, 38, acc_N);
    _mav_put_int16_t(buf, 40, acc_E);
    _mav_put_int16_t(buf, 42, acc_G);
    _mav_put_int16_t(buf, 44, angu_vel_X);
    _mav_put_int16_t(buf, 46, angu_vel_Y);
    _mav_put_int16_t(buf, 48, angu_vel_Z);
    _mav_put_int16_t(buf, 50, ctrl_rudder_1);
    _mav_put_int16_t(buf, 52, ctrl_rudder_2);
    _mav_put_int16_t(buf, 54, ctrl_rudder_3);
    _mav_put_int16_t(buf, 56, ctrl_rudder_4);
    _mav_put_int16_t(buf, 58, fdbk_rudder_1);
    _mav_put_int16_t(buf, 60, fdbk_rudder_2);
    _mav_put_int16_t(buf, 62, fdbk_rudder_3);
    _mav_put_int16_t(buf, 64, fdbk_rudder_4);
    _mav_put_int16_t(buf, 66, attack_angu);
    _mav_put_int16_t(buf, 68, side_slip_angu);
    _mav_put_int16_t(buf, 70, throttle);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_XMT_STATUS_LEN);
#else
    mavlink_xmt_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.target_dis = target_dis;
    packet.sys_stat = sys_stat;
    packet.sys_data = sys_data;
    packet.atitude = atitude;
    packet.speed_N = speed_N;
    packet.speed_E = speed_E;
    packet.speed_G = speed_G;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.campass = campass;
    packet.acc_N = acc_N;
    packet.acc_E = acc_E;
    packet.acc_G = acc_G;
    packet.angu_vel_X = angu_vel_X;
    packet.angu_vel_Y = angu_vel_Y;
    packet.angu_vel_Z = angu_vel_Z;
    packet.ctrl_rudder_1 = ctrl_rudder_1;
    packet.ctrl_rudder_2 = ctrl_rudder_2;
    packet.ctrl_rudder_3 = ctrl_rudder_3;
    packet.ctrl_rudder_4 = ctrl_rudder_4;
    packet.fdbk_rudder_1 = fdbk_rudder_1;
    packet.fdbk_rudder_2 = fdbk_rudder_2;
    packet.fdbk_rudder_3 = fdbk_rudder_3;
    packet.fdbk_rudder_4 = fdbk_rudder_4;
    packet.attack_angu = attack_angu;
    packet.side_slip_angu = side_slip_angu;
    packet.throttle = throttle;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_XMT_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_XMT_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
}

/**
 * @brief Encode a xmt_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param xmt_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_xmt_status_encode(uint32_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_xmt_status_t* xmt_status)
{
    return mavlink_msg_xmt_status_pack(system_id, component_id, msg, xmt_status->time_boot_ms, xmt_status->lat, xmt_status->lon, xmt_status->atitude, xmt_status->speed_N, xmt_status->speed_E, xmt_status->speed_G, xmt_status->yaw, xmt_status->pitch, xmt_status->campass, xmt_status->acc_N, xmt_status->acc_E, xmt_status->acc_G, xmt_status->angu_vel_X, xmt_status->angu_vel_Y, xmt_status->angu_vel_Z, xmt_status->ctrl_rudder_1, xmt_status->ctrl_rudder_2, xmt_status->ctrl_rudder_3, xmt_status->ctrl_rudder_4, xmt_status->fdbk_rudder_1, xmt_status->fdbk_rudder_2, xmt_status->fdbk_rudder_3, xmt_status->fdbk_rudder_4, xmt_status->attack_angu, xmt_status->side_slip_angu, xmt_status->throttle, xmt_status->target_dis, xmt_status->sys_stat, xmt_status->sys_data);
}

/**
 * @brief Encode a xmt_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param xmt_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_xmt_status_encode_chan(uint32_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_xmt_status_t* xmt_status)
{
    return mavlink_msg_xmt_status_pack_chan(system_id, component_id, chan, msg, xmt_status->time_boot_ms, xmt_status->lat, xmt_status->lon, xmt_status->atitude, xmt_status->speed_N, xmt_status->speed_E, xmt_status->speed_G, xmt_status->yaw, xmt_status->pitch, xmt_status->campass, xmt_status->acc_N, xmt_status->acc_E, xmt_status->acc_G, xmt_status->angu_vel_X, xmt_status->angu_vel_Y, xmt_status->angu_vel_Z, xmt_status->ctrl_rudder_1, xmt_status->ctrl_rudder_2, xmt_status->ctrl_rudder_3, xmt_status->ctrl_rudder_4, xmt_status->fdbk_rudder_1, xmt_status->fdbk_rudder_2, xmt_status->fdbk_rudder_3, xmt_status->fdbk_rudder_4, xmt_status->attack_angu, xmt_status->side_slip_angu, xmt_status->throttle, xmt_status->target_dis, xmt_status->sys_stat, xmt_status->sys_data);
}

/**
 * @brief Encode a xmt_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param xmt_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_xmt_status_encode_status(uint32_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_xmt_status_t* xmt_status)
{
    return mavlink_msg_xmt_status_pack_status(system_id, component_id, _status, msg,  xmt_status->time_boot_ms, xmt_status->lat, xmt_status->lon, xmt_status->atitude, xmt_status->speed_N, xmt_status->speed_E, xmt_status->speed_G, xmt_status->yaw, xmt_status->pitch, xmt_status->campass, xmt_status->acc_N, xmt_status->acc_E, xmt_status->acc_G, xmt_status->angu_vel_X, xmt_status->angu_vel_Y, xmt_status->angu_vel_Z, xmt_status->ctrl_rudder_1, xmt_status->ctrl_rudder_2, xmt_status->ctrl_rudder_3, xmt_status->ctrl_rudder_4, xmt_status->fdbk_rudder_1, xmt_status->fdbk_rudder_2, xmt_status->fdbk_rudder_3, xmt_status->fdbk_rudder_4, xmt_status->attack_angu, xmt_status->side_slip_angu, xmt_status->throttle, xmt_status->target_dis, xmt_status->sys_stat, xmt_status->sys_data);
}

/**
 * @brief Send a xmt_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param lat [degree] latitude of vehicle, [-180,180], LSB：10e-7)
 * @param lon [degree] longitude of vehicle, [-90,90], LSB：10e-7
 * @param atitude [m] atitude of vehicle, [-500,5000], LSB：0.1，offset： -500
 * @param speed_N [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_E [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param speed_G [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 * @param yaw [degree] Yaw of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param pitch [degree] Pitch of vehicle, [-90,90], LSB：180/(2^15-1)
 * @param campass [degree] Campass of vehicle, [-180,180], LSB：180/(2^15-1)
 * @param acc_N [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_E [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param acc_G [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 * @param angu_vel_X [degree/s] X-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Y [degree/s] Y-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param angu_vel_Z [degree/s] Z-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 * @param ctrl_rudder_1 [degree] rudder 1 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_2 [degree] rudder 2 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_3 [degree] rudder 3 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param ctrl_rudder_4 [degree] rudder 4 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_1 [degree] rudder 1 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_2 [degree] rudder 2 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_3 [degree] rudder 3 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param fdbk_rudder_4 [degree] rudder 4 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 * @param attack_angu [degree] Attack angular, [-30,30]，LSB：30/(2^15-1)
 * @param side_slip_angu [degree] side slip angular, [-30,30]，LSB: 30/(2^15-1)
 * @param throttle [degree] throttle, [0,1]，LSB: 0.0001
 * @param target_dis [m] distance between target and vehicle, LSB: 0.01
 * @param sys_stat [m] system status
 * @param sys_data [m] system data
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_xmt_status_send(mavlink_channel_t chan, uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, int16_t speed_N, int16_t speed_E, int16_t speed_G, int16_t yaw, int16_t pitch, int16_t campass, int16_t acc_N, int16_t acc_E, int16_t acc_G, int16_t angu_vel_X, int16_t angu_vel_Y, int16_t angu_vel_Z, int16_t ctrl_rudder_1, int16_t ctrl_rudder_2, int16_t ctrl_rudder_3, int16_t ctrl_rudder_4, int16_t fdbk_rudder_1, int16_t fdbk_rudder_2, int16_t fdbk_rudder_3, int16_t fdbk_rudder_4, int16_t attack_angu, int16_t side_slip_angu, int16_t throttle, uint32_t target_dis, uint32_t sys_stat, uint32_t sys_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_XMT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint32_t(buf, 12, target_dis);
    _mav_put_uint32_t(buf, 16, sys_stat);
    _mav_put_uint32_t(buf, 20, sys_data);
    _mav_put_uint16_t(buf, 24, atitude);
    _mav_put_int16_t(buf, 26, speed_N);
    _mav_put_int16_t(buf, 28, speed_E);
    _mav_put_int16_t(buf, 30, speed_G);
    _mav_put_int16_t(buf, 32, yaw);
    _mav_put_int16_t(buf, 34, pitch);
    _mav_put_int16_t(buf, 36, campass);
    _mav_put_int16_t(buf, 38, acc_N);
    _mav_put_int16_t(buf, 40, acc_E);
    _mav_put_int16_t(buf, 42, acc_G);
    _mav_put_int16_t(buf, 44, angu_vel_X);
    _mav_put_int16_t(buf, 46, angu_vel_Y);
    _mav_put_int16_t(buf, 48, angu_vel_Z);
    _mav_put_int16_t(buf, 50, ctrl_rudder_1);
    _mav_put_int16_t(buf, 52, ctrl_rudder_2);
    _mav_put_int16_t(buf, 54, ctrl_rudder_3);
    _mav_put_int16_t(buf, 56, ctrl_rudder_4);
    _mav_put_int16_t(buf, 58, fdbk_rudder_1);
    _mav_put_int16_t(buf, 60, fdbk_rudder_2);
    _mav_put_int16_t(buf, 62, fdbk_rudder_3);
    _mav_put_int16_t(buf, 64, fdbk_rudder_4);
    _mav_put_int16_t(buf, 66, attack_angu);
    _mav_put_int16_t(buf, 68, side_slip_angu);
    _mav_put_int16_t(buf, 70, throttle);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_XMT_STATUS, buf, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
#else
    mavlink_xmt_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.lat = lat;
    packet.lon = lon;
    packet.target_dis = target_dis;
    packet.sys_stat = sys_stat;
    packet.sys_data = sys_data;
    packet.atitude = atitude;
    packet.speed_N = speed_N;
    packet.speed_E = speed_E;
    packet.speed_G = speed_G;
    packet.yaw = yaw;
    packet.pitch = pitch;
    packet.campass = campass;
    packet.acc_N = acc_N;
    packet.acc_E = acc_E;
    packet.acc_G = acc_G;
    packet.angu_vel_X = angu_vel_X;
    packet.angu_vel_Y = angu_vel_Y;
    packet.angu_vel_Z = angu_vel_Z;
    packet.ctrl_rudder_1 = ctrl_rudder_1;
    packet.ctrl_rudder_2 = ctrl_rudder_2;
    packet.ctrl_rudder_3 = ctrl_rudder_3;
    packet.ctrl_rudder_4 = ctrl_rudder_4;
    packet.fdbk_rudder_1 = fdbk_rudder_1;
    packet.fdbk_rudder_2 = fdbk_rudder_2;
    packet.fdbk_rudder_3 = fdbk_rudder_3;
    packet.fdbk_rudder_4 = fdbk_rudder_4;
    packet.attack_angu = attack_angu;
    packet.side_slip_angu = side_slip_angu;
    packet.throttle = throttle;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_XMT_STATUS, (const char *)&packet, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
#endif
}

/**
 * @brief Send a xmt_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_xmt_status_send_struct(mavlink_channel_t chan, const mavlink_xmt_status_t* xmt_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_xmt_status_send(chan, xmt_status->time_boot_ms, xmt_status->lat, xmt_status->lon, xmt_status->atitude, xmt_status->speed_N, xmt_status->speed_E, xmt_status->speed_G, xmt_status->yaw, xmt_status->pitch, xmt_status->campass, xmt_status->acc_N, xmt_status->acc_E, xmt_status->acc_G, xmt_status->angu_vel_X, xmt_status->angu_vel_Y, xmt_status->angu_vel_Z, xmt_status->ctrl_rudder_1, xmt_status->ctrl_rudder_2, xmt_status->ctrl_rudder_3, xmt_status->ctrl_rudder_4, xmt_status->fdbk_rudder_1, xmt_status->fdbk_rudder_2, xmt_status->fdbk_rudder_3, xmt_status->fdbk_rudder_4, xmt_status->attack_angu, xmt_status->side_slip_angu, xmt_status->throttle, xmt_status->target_dis, xmt_status->sys_stat, xmt_status->sys_data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_XMT_STATUS, (const char *)xmt_status, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_XMT_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_xmt_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, int32_t lat, int32_t lon, uint16_t atitude, int16_t speed_N, int16_t speed_E, int16_t speed_G, int16_t yaw, int16_t pitch, int16_t campass, int16_t acc_N, int16_t acc_E, int16_t acc_G, int16_t angu_vel_X, int16_t angu_vel_Y, int16_t angu_vel_Z, int16_t ctrl_rudder_1, int16_t ctrl_rudder_2, int16_t ctrl_rudder_3, int16_t ctrl_rudder_4, int16_t fdbk_rudder_1, int16_t fdbk_rudder_2, int16_t fdbk_rudder_3, int16_t fdbk_rudder_4, int16_t attack_angu, int16_t side_slip_angu, int16_t throttle, uint32_t target_dis, uint32_t sys_stat, uint32_t sys_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int32_t(buf, 4, lat);
    _mav_put_int32_t(buf, 8, lon);
    _mav_put_uint32_t(buf, 12, target_dis);
    _mav_put_uint32_t(buf, 16, sys_stat);
    _mav_put_uint32_t(buf, 20, sys_data);
    _mav_put_uint16_t(buf, 24, atitude);
    _mav_put_int16_t(buf, 26, speed_N);
    _mav_put_int16_t(buf, 28, speed_E);
    _mav_put_int16_t(buf, 30, speed_G);
    _mav_put_int16_t(buf, 32, yaw);
    _mav_put_int16_t(buf, 34, pitch);
    _mav_put_int16_t(buf, 36, campass);
    _mav_put_int16_t(buf, 38, acc_N);
    _mav_put_int16_t(buf, 40, acc_E);
    _mav_put_int16_t(buf, 42, acc_G);
    _mav_put_int16_t(buf, 44, angu_vel_X);
    _mav_put_int16_t(buf, 46, angu_vel_Y);
    _mav_put_int16_t(buf, 48, angu_vel_Z);
    _mav_put_int16_t(buf, 50, ctrl_rudder_1);
    _mav_put_int16_t(buf, 52, ctrl_rudder_2);
    _mav_put_int16_t(buf, 54, ctrl_rudder_3);
    _mav_put_int16_t(buf, 56, ctrl_rudder_4);
    _mav_put_int16_t(buf, 58, fdbk_rudder_1);
    _mav_put_int16_t(buf, 60, fdbk_rudder_2);
    _mav_put_int16_t(buf, 62, fdbk_rudder_3);
    _mav_put_int16_t(buf, 64, fdbk_rudder_4);
    _mav_put_int16_t(buf, 66, attack_angu);
    _mav_put_int16_t(buf, 68, side_slip_angu);
    _mav_put_int16_t(buf, 70, throttle);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_XMT_STATUS, buf, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
#else
    mavlink_xmt_status_t *packet = (mavlink_xmt_status_t *)msgbuf;
    packet->time_boot_ms = time_boot_ms;
    packet->lat = lat;
    packet->lon = lon;
    packet->target_dis = target_dis;
    packet->sys_stat = sys_stat;
    packet->sys_data = sys_data;
    packet->atitude = atitude;
    packet->speed_N = speed_N;
    packet->speed_E = speed_E;
    packet->speed_G = speed_G;
    packet->yaw = yaw;
    packet->pitch = pitch;
    packet->campass = campass;
    packet->acc_N = acc_N;
    packet->acc_E = acc_E;
    packet->acc_G = acc_G;
    packet->angu_vel_X = angu_vel_X;
    packet->angu_vel_Y = angu_vel_Y;
    packet->angu_vel_Z = angu_vel_Z;
    packet->ctrl_rudder_1 = ctrl_rudder_1;
    packet->ctrl_rudder_2 = ctrl_rudder_2;
    packet->ctrl_rudder_3 = ctrl_rudder_3;
    packet->ctrl_rudder_4 = ctrl_rudder_4;
    packet->fdbk_rudder_1 = fdbk_rudder_1;
    packet->fdbk_rudder_2 = fdbk_rudder_2;
    packet->fdbk_rudder_3 = fdbk_rudder_3;
    packet->fdbk_rudder_4 = fdbk_rudder_4;
    packet->attack_angu = attack_angu;
    packet->side_slip_angu = side_slip_angu;
    packet->throttle = throttle;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_XMT_STATUS, (const char *)packet, MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN, MAVLINK_MSG_ID_XMT_STATUS_LEN, MAVLINK_MSG_ID_XMT_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE XMT_STATUS UNPACKING


/**
 * @brief Get field time_boot_ms from xmt_status message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_xmt_status_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field lat from xmt_status message
 *
 * @return [degree] latitude of vehicle, [-180,180], LSB：10e-7)
 */
static inline int32_t mavlink_msg_xmt_status_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field lon from xmt_status message
 *
 * @return [degree] longitude of vehicle, [-90,90], LSB：10e-7
 */
static inline int32_t mavlink_msg_xmt_status_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field atitude from xmt_status message
 *
 * @return [m] atitude of vehicle, [-500,5000], LSB：0.1，offset： -500
 */
static inline uint16_t mavlink_msg_xmt_status_get_atitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field speed_N from xmt_status message
 *
 * @return [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_speed_N(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  26);
}

/**
 * @brief Get field speed_E from xmt_status message
 *
 * @return [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_speed_E(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  28);
}

/**
 * @brief Get field speed_G from xmt_status message
 *
 * @return [m/s] north speed of vehicle, [-100,100]	LSB：100/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_speed_G(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  30);
}

/**
 * @brief Get field yaw from xmt_status message
 *
 * @return [degree] Yaw of vehicle, [-180,180], LSB：180/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  32);
}

/**
 * @brief Get field pitch from xmt_status message
 *
 * @return [degree] Pitch of vehicle, [-90,90], LSB：180/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  34);
}

/**
 * @brief Get field campass from xmt_status message
 *
 * @return [degree] Campass of vehicle, [-180,180], LSB：180/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_campass(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  36);
}

/**
 * @brief Get field acc_N from xmt_status message
 *
 * @return [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_acc_N(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  38);
}

/**
 * @brief Get field acc_E from xmt_status message
 *
 * @return [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_acc_E(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  40);
}

/**
 * @brief Get field acc_G from xmt_status message
 *
 * @return [m/s^2] north acceleration of vehicle, [-160,160], LSB：160/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_acc_G(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  42);
}

/**
 * @brief Get field angu_vel_X from xmt_status message
 *
 * @return [degree/s] X-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_angu_vel_X(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  44);
}

/**
 * @brief Get field angu_vel_Y from xmt_status message
 *
 * @return [degree/s] Y-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_angu_vel_Y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  46);
}

/**
 * @brief Get field angu_vel_Z from xmt_status message
 *
 * @return [degree/s] Z-axis angular velocity of vehicle, [-400,400], LSB: 400/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_angu_vel_Z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  48);
}

/**
 * @brief Get field ctrl_rudder_1 from xmt_status message
 *
 * @return [degree] rudder 1 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_ctrl_rudder_1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  50);
}

/**
 * @brief Get field ctrl_rudder_2 from xmt_status message
 *
 * @return [degree] rudder 2 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_ctrl_rudder_2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  52);
}

/**
 * @brief Get field ctrl_rudder_3 from xmt_status message
 *
 * @return [degree] rudder 3 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_ctrl_rudder_3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  54);
}

/**
 * @brief Get field ctrl_rudder_4 from xmt_status message
 *
 * @return [degree] rudder 4 angular control of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_ctrl_rudder_4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  56);
}

/**
 * @brief Get field fdbk_rudder_1 from xmt_status message
 *
 * @return [degree] rudder 1 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_fdbk_rudder_1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  58);
}

/**
 * @brief Get field fdbk_rudder_2 from xmt_status message
 *
 * @return [degree] rudder 2 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_fdbk_rudder_2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  60);
}

/**
 * @brief Get field fdbk_rudder_3 from xmt_status message
 *
 * @return [degree] rudder 3 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_fdbk_rudder_3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  62);
}

/**
 * @brief Get field fdbk_rudder_4 from xmt_status message
 *
 * @return [degree] rudder 4 angular feedback of vehicle, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_fdbk_rudder_4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  64);
}

/**
 * @brief Get field attack_angu from xmt_status message
 *
 * @return [degree] Attack angular, [-30,30]，LSB：30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_attack_angu(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  66);
}

/**
 * @brief Get field side_slip_angu from xmt_status message
 *
 * @return [degree] side slip angular, [-30,30]，LSB: 30/(2^15-1)
 */
static inline int16_t mavlink_msg_xmt_status_get_side_slip_angu(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  68);
}

/**
 * @brief Get field throttle from xmt_status message
 *
 * @return [degree] throttle, [0,1]，LSB: 0.0001
 */
static inline int16_t mavlink_msg_xmt_status_get_throttle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  70);
}

/**
 * @brief Get field target_dis from xmt_status message
 *
 * @return [m] distance between target and vehicle, LSB: 0.01
 */
static inline uint32_t mavlink_msg_xmt_status_get_target_dis(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field sys_stat from xmt_status message
 *
 * @return [m] system status
 */
static inline uint32_t mavlink_msg_xmt_status_get_sys_stat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field sys_data from xmt_status message
 *
 * @return [m] system data
 */
static inline uint32_t mavlink_msg_xmt_status_get_sys_data(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Decode a xmt_status message into a struct
 *
 * @param msg The message to decode
 * @param xmt_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_xmt_status_decode(const mavlink_message_t* msg, mavlink_xmt_status_t* xmt_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    xmt_status->time_boot_ms = mavlink_msg_xmt_status_get_time_boot_ms(msg);
    xmt_status->lat = mavlink_msg_xmt_status_get_lat(msg);
    xmt_status->lon = mavlink_msg_xmt_status_get_lon(msg);
    xmt_status->target_dis = mavlink_msg_xmt_status_get_target_dis(msg);
    xmt_status->sys_stat = mavlink_msg_xmt_status_get_sys_stat(msg);
    xmt_status->sys_data = mavlink_msg_xmt_status_get_sys_data(msg);
    xmt_status->atitude = mavlink_msg_xmt_status_get_atitude(msg);
    xmt_status->speed_N = mavlink_msg_xmt_status_get_speed_N(msg);
    xmt_status->speed_E = mavlink_msg_xmt_status_get_speed_E(msg);
    xmt_status->speed_G = mavlink_msg_xmt_status_get_speed_G(msg);
    xmt_status->yaw = mavlink_msg_xmt_status_get_yaw(msg);
    xmt_status->pitch = mavlink_msg_xmt_status_get_pitch(msg);
    xmt_status->campass = mavlink_msg_xmt_status_get_campass(msg);
    xmt_status->acc_N = mavlink_msg_xmt_status_get_acc_N(msg);
    xmt_status->acc_E = mavlink_msg_xmt_status_get_acc_E(msg);
    xmt_status->acc_G = mavlink_msg_xmt_status_get_acc_G(msg);
    xmt_status->angu_vel_X = mavlink_msg_xmt_status_get_angu_vel_X(msg);
    xmt_status->angu_vel_Y = mavlink_msg_xmt_status_get_angu_vel_Y(msg);
    xmt_status->angu_vel_Z = mavlink_msg_xmt_status_get_angu_vel_Z(msg);
    xmt_status->ctrl_rudder_1 = mavlink_msg_xmt_status_get_ctrl_rudder_1(msg);
    xmt_status->ctrl_rudder_2 = mavlink_msg_xmt_status_get_ctrl_rudder_2(msg);
    xmt_status->ctrl_rudder_3 = mavlink_msg_xmt_status_get_ctrl_rudder_3(msg);
    xmt_status->ctrl_rudder_4 = mavlink_msg_xmt_status_get_ctrl_rudder_4(msg);
    xmt_status->fdbk_rudder_1 = mavlink_msg_xmt_status_get_fdbk_rudder_1(msg);
    xmt_status->fdbk_rudder_2 = mavlink_msg_xmt_status_get_fdbk_rudder_2(msg);
    xmt_status->fdbk_rudder_3 = mavlink_msg_xmt_status_get_fdbk_rudder_3(msg);
    xmt_status->fdbk_rudder_4 = mavlink_msg_xmt_status_get_fdbk_rudder_4(msg);
    xmt_status->attack_angu = mavlink_msg_xmt_status_get_attack_angu(msg);
    xmt_status->side_slip_angu = mavlink_msg_xmt_status_get_side_slip_angu(msg);
    xmt_status->throttle = mavlink_msg_xmt_status_get_throttle(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_XMT_STATUS_LEN? msg->len : MAVLINK_MSG_ID_XMT_STATUS_LEN;
        memset(xmt_status, 0, MAVLINK_MSG_ID_XMT_STATUS_LEN);
    memcpy(xmt_status, _MAV_PAYLOAD(msg), len);
#endif

}
