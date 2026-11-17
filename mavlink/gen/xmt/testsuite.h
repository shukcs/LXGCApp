/** @file
 *    @brief MAVLink comm protocol testsuite generated from xmt.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef XMT_TESTSUITE_H
#define XMT_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_xmt(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_xmt(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_xmt_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_XMT_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_xmt_status_t packet_in = {
        963497464,963497672,963497880,963498088,963498296,963498504,18483,18587,18691,18795,18899,19003,19107,19211,19315,19419,19523,19627,19731,19835,19939,20043,20147,20251,20355,20459,20563,20667,20771,20875
    };
    mavlink_xmt_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.target_dis = packet_in.target_dis;
        packet1.sys_stat = packet_in.sys_stat;
        packet1.sys_data = packet_in.sys_data;
        packet1.atitude = packet_in.atitude;
        packet1.speed_N = packet_in.speed_N;
        packet1.speed_E = packet_in.speed_E;
        packet1.speed_G = packet_in.speed_G;
        packet1.yaw = packet_in.yaw;
        packet1.pitch = packet_in.pitch;
        packet1.campass = packet_in.campass;
        packet1.acc_N = packet_in.acc_N;
        packet1.acc_E = packet_in.acc_E;
        packet1.acc_G = packet_in.acc_G;
        packet1.angu_vel_X = packet_in.angu_vel_X;
        packet1.angu_vel_Y = packet_in.angu_vel_Y;
        packet1.angu_vel_Z = packet_in.angu_vel_Z;
        packet1.ctrl_rudder_1 = packet_in.ctrl_rudder_1;
        packet1.ctrl_rudder_2 = packet_in.ctrl_rudder_2;
        packet1.ctrl_rudder_3 = packet_in.ctrl_rudder_3;
        packet1.ctrl_rudder_4 = packet_in.ctrl_rudder_4;
        packet1.fdbk_rudder_1 = packet_in.fdbk_rudder_1;
        packet1.fdbk_rudder_2 = packet_in.fdbk_rudder_2;
        packet1.fdbk_rudder_3 = packet_in.fdbk_rudder_3;
        packet1.fdbk_rudder_4 = packet_in.fdbk_rudder_4;
        packet1.attack_angu = packet_in.attack_angu;
        packet1.side_slip_angu = packet_in.side_slip_angu;
        packet1.throttle = packet_in.throttle;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_XMT_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_xmt_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_xmt_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_xmt_status_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.speed_N , packet1.speed_E , packet1.speed_G , packet1.yaw , packet1.pitch , packet1.campass , packet1.acc_N , packet1.acc_E , packet1.acc_G , packet1.angu_vel_X , packet1.angu_vel_Y , packet1.angu_vel_Z , packet1.ctrl_rudder_1 , packet1.ctrl_rudder_2 , packet1.ctrl_rudder_3 , packet1.ctrl_rudder_4 , packet1.fdbk_rudder_1 , packet1.fdbk_rudder_2 , packet1.fdbk_rudder_3 , packet1.fdbk_rudder_4 , packet1.attack_angu , packet1.side_slip_angu , packet1.throttle , packet1.target_dis , packet1.sys_stat , packet1.sys_data );
    mavlink_msg_xmt_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_xmt_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.speed_N , packet1.speed_E , packet1.speed_G , packet1.yaw , packet1.pitch , packet1.campass , packet1.acc_N , packet1.acc_E , packet1.acc_G , packet1.angu_vel_X , packet1.angu_vel_Y , packet1.angu_vel_Z , packet1.ctrl_rudder_1 , packet1.ctrl_rudder_2 , packet1.ctrl_rudder_3 , packet1.ctrl_rudder_4 , packet1.fdbk_rudder_1 , packet1.fdbk_rudder_2 , packet1.fdbk_rudder_3 , packet1.fdbk_rudder_4 , packet1.attack_angu , packet1.side_slip_angu , packet1.throttle , packet1.target_dis , packet1.sys_stat , packet1.sys_data );
    mavlink_msg_xmt_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_xmt_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_xmt_status_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.speed_N , packet1.speed_E , packet1.speed_G , packet1.yaw , packet1.pitch , packet1.campass , packet1.acc_N , packet1.acc_E , packet1.acc_G , packet1.angu_vel_X , packet1.angu_vel_Y , packet1.angu_vel_Z , packet1.ctrl_rudder_1 , packet1.ctrl_rudder_2 , packet1.ctrl_rudder_3 , packet1.ctrl_rudder_4 , packet1.fdbk_rudder_1 , packet1.fdbk_rudder_2 , packet1.fdbk_rudder_3 , packet1.fdbk_rudder_4 , packet1.attack_angu , packet1.side_slip_angu , packet1.throttle , packet1.target_dis , packet1.sys_stat , packet1.sys_data );
    mavlink_msg_xmt_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("XMT_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_XMT_STATUS) != NULL);
#endif
}

static void mavlink_test_task_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TASK_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_task_status_t packet_in = {
        963497464,963497672,963497880,17859,175,242
    };
    mavlink_task_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.atitude = packet_in.atitude;
        packet1.sin_Y_mode = packet_in.sin_Y_mode;
        packet1.trigger_c = packet_in.trigger_c;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TASK_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_task_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.sin_Y_mode , packet1.trigger_c );
    mavlink_msg_task_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.sin_Y_mode , packet1.trigger_c );
    mavlink_msg_task_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_task_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.sin_Y_mode , packet1.trigger_c );
    mavlink_msg_task_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TASK_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TASK_STATUS) != NULL);
#endif
}

static void mavlink_test_task_status_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TASK_STATUS_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_task_status_ack_t packet_in = {
        963497464,963497672,963497880,17859,175,242,53
    };
    mavlink_task_status_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.atitude = packet_in.atitude;
        packet1.sin_Y_mode = packet_in.sin_Y_mode;
        packet1.trigger_c = packet_in.trigger_c;
        packet1.result = packet_in.result;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TASK_STATUS_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TASK_STATUS_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_task_status_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_ack_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.sin_Y_mode , packet1.trigger_c , packet1.result );
    mavlink_msg_task_status_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.sin_Y_mode , packet1.trigger_c , packet1.result );
    mavlink_msg_task_status_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_task_status_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_task_status_ack_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.lat , packet1.lon , packet1.atitude , packet1.sin_Y_mode , packet1.trigger_c , packet1.result );
    mavlink_msg_task_status_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TASK_STATUS_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TASK_STATUS_ACK) != NULL);
#endif
}

static void mavlink_test_xmt(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_xmt_status(system_id, component_id, last_msg);
    mavlink_test_task_status(system_id, component_id, last_msg);
    mavlink_test_task_status_ack(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // XMT_TESTSUITE_H
