import cv2 as cv
import matplotlib.colors as mcolors
import numpy as np

from .geometry import (EDGES_INDICES, Rt_from_Transform, cam_info_to_matrices,
                       object_points)
from .rect import Rect

COLOR_TABLE = [
    # matplotlib tableau palette
    # https://matplotlib.org/stable/gallery/color/named_colors.html
    (180, 119, 31),  # tab:blue
    (14, 127, 255),  # tab:orange
    (44, 160, 44),  # tab:green
    (40, 39, 214),  # tab:red
    (189, 103, 148),  # tab:purple
    (75, 86, 140),  # tab:brown
    (194, 119, 227),  # tab:pink
    (127, 127, 127),  # tab:gray
    (34, 189, 188),  # tab:olive
    (207, 190, 23),  # tab:cyan
]


def random_color(idx):
    c = COLOR_TABLE[idx % len(COLOR_TABLE)]
    return c


def object_color(obj, color):
    if color == 'id':
        color = random_color(obj.id)
    elif color == 'label':
        color = random_color(obj.label)
    else:
        color = tuple(int(c * 255) for c in reversed(mcolors.to_rgb(color)))
    return color


def object_label(obj, label_fmt='', classes=None):
    if not label_fmt:
        return ''
    obj_dict = {
        s: getattr(obj, s, None)
        for s in obj.get_fields_and_field_types().keys()
    }
    if classes:
        obj_dict['cls'] = classes[obj.label]
    label = label_fmt.format(**obj_dict)
    return label


def draw_rect_and_label(img, p0, p1, label, color, font_size=1.0):
    font_type = cv.FONT_HERSHEY_PLAIN
    font_weight = int(round(font_size))
    text_color = (255, 255, 255)
    thickness = int(round(font_weight * 2))
    (text_w, text_h), baseline = cv.getTextSize(label, font_type, font_size,
                                                font_weight)
    label_w = text_w + 2
    label_h = text_h + 2 * thickness
    if p1[0] + text_w <= img.shape[1]:  # top right corner
        text_org = p1[0] + 2, p0[1] + baseline + label_h // 2
        label_p0 = p1[0], p0[1]
        label_p1 = label_p0[0] + label_w, label_p0[1] + label_h
    else:  # top left corner
        text_org = p0[0] - text_w, p0[1] + baseline + label_h // 2
        label_p0 = p0[0] - label_w, p0[1]
        label_p1 = label_p0[0] + label_w, label_p0[1] + label_h

    cv.rectangle(img, p0, p1, color, thickness)
    if label:
        cv.rectangle(img, label_p0, label_p1, color=color, thickness=-1)
        cv.rectangle(img, label_p0, label_p1, color=color, thickness=thickness)
        cv.putText(img, label, text_org, font_type, font_size, text_color,
                   font_weight, cv.LINE_AA)


def object_rect(obj):
    return Rect(obj.x, obj.y, obj.width, obj.height)


def draw_object(img, obj, color, label_fmt='', classes=None, font_size=1.0):
    color = object_color(obj, color)
    label = object_label(obj, label_fmt, classes)
    r = object_rect(obj)
    draw_rect_and_label(img, r.tl(), r.br(), label, color, font_size)


def draw_object3d(img, obj, cam_info, color, tf=None, rectified=False):
    Rt = Rt_from_Transform(tf) if tf else None
    pts = object_points(obj, Rt)
    if np.any(pts[:, 2] <= 0):
        # skip objects behind camera
        return
    r = cam_info_to_matrices(cam_info)
    if rectified:
        K = r.P[:, :3]
        D = np.zeros(5)
        rvec = np.zeros(3)
        tvec = np.array([r.P[0, 3] / r.P[0, 0], r.P[1, 3] / r.P[1, 1], 0])
    else:
        K = r.K
        D = r.D
        rvec, _ = cv.Rodrigues(np.linalg.inv(r.R))
        tvec = np.zeros(3)
    ipts, _ = cv.projectPoints(pts, rvec, tvec, K, D)
    ipts = ipts.astype(int).reshape(-1, 2)
    for i1, i2 in EDGES_INDICES:
        p1 = tuple(ipts[i1])
        p2 = tuple(ipts[i2])
        cv.line(img, p1, p2, color, 1, cv.LINE_AA)
