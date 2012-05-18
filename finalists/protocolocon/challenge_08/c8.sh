#!/bin/bash

./c8 | md5sum | cut -d\  -f1
