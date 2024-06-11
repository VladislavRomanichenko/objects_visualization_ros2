import cv2 as cv
import numpy as np
import rclpy
from cv_bridge import CvBridge
from geometry_msgs.msg import Point, Pose, Quaternion, Vector3
from objects_msgs.msg import Object, Object2D, Object2DArray, ObjectArray
from rclpy.node import Node
from sensor_msgs.msg import CameraInfo, Image
from std_msgs.msg import Header

from .utils import draw_object3d, object_points, random_color


class RandomObjectPublisher(Node):
    def __init__(self):
        super().__init__('publish_random_objects')
        self.declare_parameter('im_width', 640)
        self.declare_parameter('im_height', 480)
        self.declare_parameter('fov', 90.0)
        self.declare_parameter('nclasses', 5)
        self.declare_parameter('nobjects', 3)
        self.declare_parameter('frame_id', 'random_objects')
        self.declare_parameter('rate', 1.0)

        self.im_width = self.get_parameter(
            'im_width').get_parameter_value().integer_value
        self.im_height = self.get_parameter(
            'im_height').get_parameter_value().integer_value
        self.fov = self.get_parameter('fov').get_parameter_value().double_value
        self.nclasses = self.get_parameter(
            'nclasses').get_parameter_value().integer_value
        self.nobjects = self.get_parameter(
            'nobjects').get_parameter_value().integer_value
        self.frame_id = self.get_parameter(
            'frame_id').get_parameter_value().string_value
        self.rate = self.get_parameter(
            'rate').get_parameter_value().double_value

        f = self.im_width / (2 * np.tan(np.deg2rad(self.fov / 2)))
        self.K = np.array([
            [f, 0, (self.im_width - 1) / 2],
            [0, f, (self.im_height - 1) / 2],
            [0, 0, 1],
        ])

        self.bridge = CvBridge()
        self.pub_image = self.create_publisher(Image, 'image', 1)
        self.pub_cam_info = self.create_publisher(CameraInfo, 'camera_info', 1)
        self.pub_objects2d = self.create_publisher(Object2DArray, 'objects2d',
                                                   1)
        self.pub_objects3d = self.create_publisher(ObjectArray, 'objects3d', 1)
        self.create_timer(1.0 / self.rate, self.publish_data)

    def publish_data(self):
        header = Header(frame_id=self.frame_id,
                        stamp=self.get_clock().now().to_msg())
        objects2d_msg = Object2DArray(header=header)
        objects3d_msg = ObjectArray(header=header)

        cam_info_msg = CameraInfo(header=header)
        cam_info_msg.k = self.K.ravel().tolist()
        cam_info_msg.d = np.zeros(5).tolist()
        P = np.hstack((self.K, np.zeros((3, 1))))
        cam_info_msg.p = P.ravel().tolist()
        cam_info_msg.r = np.eye(3).ravel().tolist()

        image = np.full((self.im_height, self.im_width, 3), 255, np.uint8)
        for id in range(self.nobjects):
            label = np.random.randint(self.nclasses)
            score = np.random.rand()

            # generate cuboid in 3D space
            x = np.random.uniform(-10, 10)
            y = np.random.uniform(-10, 10)
            z = np.random.uniform(10, 20)
            dx = np.random.uniform(0.2, 1.0)
            dy = np.random.uniform(0.2, 1.0)
            dz = np.random.uniform(0.2, 1.0)

            pose = Pose(position=Point(x=x, y=y, z=z),
                        orientation=Quaternion(x=0.0, y=0.0, z=0.0, w=1.0))
            size = Vector3(x=2 * dx, y=2 * dy, z=2 * dz)

            obj3d = Object(id=id,
                           label=label,
                           score=score,
                           pose=pose,
                           size=size)
            objects3d_msg.objects.append(obj3d)

            pts = object_points(obj3d)
            ipts, _ = cv.projectPoints(pts, np.zeros(3), np.zeros(3), self.K,
                                       np.zeros(5))
            ipts = ipts.astype(int).reshape(-1, 2)

            border = 3  # slightly enlarge object projections size
            u0 = int(ipts[:, 0].min()) - border
            u1 = int(ipts[:, 0].max()) + border
            v0 = int(ipts[:, 1].min()) - border
            v1 = int(ipts[:, 1].max()) + border

            obj = Object2D(id=id,
                           label=label,
                           score=score,
                           x=u0,
                           y=v0,
                           width=u1 - u0,
                           height=v1 - v0)
            objects2d_msg.objects.append(obj)

            color = random_color(id)
            draw_object3d(image, obj3d, cam_info_msg, color)

        image_msg = self.bridge.cv2_to_imgmsg(image, 'bgr8', header=header)
        image_msg.header.frame_id = self.frame_id
        image_msg.header.stamp = self.get_clock().now().to_msg()
        self.pub_image.publish(image_msg)

        self.pub_objects2d.publish(objects2d_msg)

        self.pub_objects3d.publish(objects3d_msg)
        self.pub_cam_info.publish(cam_info_msg)


def main(args=None):
    rclpy.init(args=args)
    node = RandomObjectPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

main()