#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 16: Malware detector ***

import sys

if __name__ == '__main__':
    result_sum_malware_counters = 0

    known_reports = int(sys.stdin.readline())
    unknown_reports = int(sys.stdin.readline())
    vector_size = int(sys.stdin.readline())

    count_safe = 0
    count_malware = 0

    safe_vector = [0 for i in range(vector_size) ]
    malware_vector = [0 for i in range(vector_size) ]

    for i in range(known_reports):
        tokens = sys.stdin.readline().rstrip().split()
        sw_type = tokens[0]

        vector = [int(tokens[i + 1]) for i in range(vector_size)]

        if sw_type == 'S':
            safe_vector = [safe_vector[i] + vector[i] for i in range(vector_size)]
            count_safe += 1
        else:
            malware_vector = [malware_vector[i] + vector[i] for i in range(vector_size)]
            count_malware += 1


    # Normalize the frequencies
    sum_safe = float(sum(safe_vector))
    safe_vector = [x / sum_safe for x in safe_vector]
    sum_malware = float(sum(malware_vector))
    malware_vector = [x / sum_malware for x in malware_vector]

    for i in range(unknown_reports):
        vector = map(int,sys.stdin.readline().rstrip().split())

        # Normalize vector
        sum_vector = float(sum(vector))
        normalized_vector = [x / sum_vector for x in vector]

        # Compare the quadratic differences
        malware_dif = sum([(a - b) ** 2.0 for a, b in zip(malware_vector, normalized_vector)])
        safe_dif = sum([(a - b) ** 2.0 for a, b in zip(safe_vector, normalized_vector)])

        if malware_dif < safe_dif:
            result_sum_malware_counters += sum(vector)

    print result_sum_malware_counters

