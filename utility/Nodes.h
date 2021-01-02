#pragma once

struct Node {
    int prev, next;
    Node() : prev(0), next(0) {}
    Node(int _prev, int _next) { prev = _prev; next = _next; }
};

