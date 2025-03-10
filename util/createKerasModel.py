
import matplotlib.pyplot as plt
import numpy as np
import argparse
import yaml
import tensorflow as tf
from tensorflow.keras import datasets, layers, models
from tensorflow import keras
from tensorflow.keras.layers import Input, Flatten
from tensorflow.keras.models import Sequential
from qkeras import *
import os

import json

def createKerasModel(layer, input_shape, kernel_size, filters):
 
    x_in = Input(input_shape, name='input_1')
    if layer == 'depthwise_conv2d':
        x = DepthwiseConv2D(
            kernel_size=kernel_size,
            use_bias=False,
            depthwise_initializer=tf.keras.initializers.Ones(), # makes debugging easy
            bias_initializer=tf.keras.initializers.Zeros(), # makes debugging easy
            name='depthwise_conv2d'
        )(x_in)
    elif layer == 'pointwise_conv2d':
        x_out = Conv2D(
            filters=filters,
            kernel_size=(1,1),
            use_bias=False,
            kernel_initializer=tf.keras.initializers.Ones(), # makes debugging easy
            bias_initializer=tf.keras.initializers.Zeros(), # makes debugging easy
            name='pointwise_conv2d'
        )(x_in)
    else:
        x= SeparableConv2D(
            filters=filters,
            kernel_size=kernel_size,
            use_bias=False,
            depthwise_initializer=tf.keras.initializers.Ones(), # makes debugging easy
            pointwise_initializer=tf.keras.initializers.Ones(), # makes debugging easy
            name = 'separable_conv2d'
    )(x_in)
    x = Flatten()(x)
    x_out = Dense(2)(x)
    kmodel = Model(inputs=x_in, outputs=x_out)
    return kmodel