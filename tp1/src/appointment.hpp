#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <cstring>

// Define an appointment (hour, minute, description)
typedef struct AppointmentItem{
    int hour;
    int minute;
    std::string description;
} Appointment;

// Define an appointment node in a linked list
typedef struct Node {
    AppointmentItem *item;
    struct Node *next;
} AppointmentNode;

// Define a linked list for appointments
typedef struct AppointmentList {
    Node *head;
    Node *tail;
    int size;
} Day;

// Functions provided for an appointment list
void init_appointment_list(AppointmentList *appointment_list);
void free_appointment_list(AppointmentList *appointment_list);
void push_appointment(AppointmentList *appointment_list, AppointmentItem **item);
bool delete_appointment(AppointmentList *appointment_list, int hour, int minute);
bool is_empty_appointment_list(AppointmentList *appointment_list);
void print_appointment_list(AppointmentList *appointment_list);
int print_appointment_list_by_date(AppointmentList *appointment_list, int hour, int minute);
int get_size_appointment_list(AppointmentList *appointment_list);

#endif
