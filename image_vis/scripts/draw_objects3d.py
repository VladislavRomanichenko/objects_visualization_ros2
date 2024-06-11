#!/bin/env python
from __future__ import division, print_function

import cv2 as cv
import rclpy
import tf2_ros
from cv_bridge import CvBridge
from message_filters import (ApproximateTimeSynchronizer, Subscriber,
                             TimeSynchronizer)
from rclpy.node import Node
from rclpy.time import Time
from sensor_msgs.msg import CameraInfo, Image
from tf2_ros import TransformException

from objects_msgs.msg import ObjectArray

from .utils import draw_object3d, object_color


class DrawObjects3D(Node):

    def __init__(self):
        super().__init__('draw_objects3d')
        self.bridge = CvBridge()

        queue_size = self.declare_parameter('queue_size', 5).value
        approximate_sync = self.declare_parameter('approximate_sync',
                                                  False).value
        self.visualize = self.declare_parameter('visualize', False).value
        self.color = self.declare_parameter('color', 'label').value
        self.rectified = self.declare_parameter('rectified', False).value
        self.camera_frame = self.declare_parameter('camera_frame', '').value
        self.line_width = self.declare_parameter('line_width', 1).value

        self.cam_info = None
        self.tf_buffer = tf2_ros.Buffer()
        self.listener = tf2_ros.TransformListener(self.tf_buffer, self)
        self.prev_time = None

        self.cam_sub = self.create_subscription(CameraInfo, 'camera_info',
                                                self.cam_callback, 1)
        subscribers = [
            Subscriber(self, Image, 'image'),
            Subscriber(self, ObjectArray, 'objects3d')
        ]
        if approximate_sync:
            sync = ApproximateTimeSynchronizer(subscribers,
                                               queue_size=queue_size,
                                               slop=0.1)
        else:
            sync = TimeSynchronizer(subscribers, queue_size=queue_size)
        sync.registerCallback(self.callback)

        self.output = self.create_publisher(Image, 'image_objects3d', 1)

        if self.visualize:
            cv.namedWindow(self.output.topic_name)

    def cam_callback(self, cam_info):
        self.cam_info = cam_info

    def callback(self, img_msg, objects):
        if self.cam_info is None:
            self.get_logger().warn('No camera info!')
            return

        msg_time = Time.from_msg(objects.header.stamp)
        if self.prev_time is not None and self.prev_time > msg_time:
            self.get_logger().warn(f'Reset tf buffer.')
            self.tf_buffer.clear()
            self.prev_time = msg_time
            return
        self.prev_time = msg_time

        camera_frame = img_msg.header.frame_id
        if self.camera_frame:
            camera_frame = self.camera_frame

        try:
            tf = self.tf_buffer.lookup_transform(camera_frame,
                                                 objects.header.frame_id,
                                                 objects.header.stamp)
        except TransformException as ex:
            self.get_logger().warn(f'tf lookup error: {ex}')
            return

        img = self.bridge.imgmsg_to_cv2(img_msg, 'bgr8')

        for obj in objects.objects:
            color = object_color(obj, self.color)
            draw_object3d(img, obj, self.cam_info, color, tf.transform,
                          self.rectified, self.line_width)

        out = self.bridge.cv2_to_imgmsg(img, 'bgr8')
        out.header = img_msg.header
        self.output.publish(out)

        if self.visualize:
            cv.imshow(self.output.topic_name, img)


def main(args=None):
    rclpy.init(args=args)
    node = DrawObjects3D()
    while rclpy.ok():
        rclpy.spin_once(node)
        if node.visualize:
            cv.waitKey(1)
    node.destroy_node()
    rclpy.shutdown()
