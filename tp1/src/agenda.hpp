#ifndef AGENDA_H
#define AGENDA_H

#include "appointment.hpp"

#define AGENDA_FILE_PATH "./data/agenda.txt"
#define AGENDA_DELIMITER '|'

// Define an item in an agenda item (month, size, appointment list)
typedef struct AgendaItem {
    int month;
    int size; // Number of days in this month
    AppointmentList *appointment_list; // Appointment lists for each day of this month
} Month;

// Define an agenda node in a linked list
typedef struct AgendaNode {
    AgendaItem *item;
    AgendaNode *next;
} AgendaNode;

// Define an agenda
typedef struct {
    AgendaNode *head;
    AgendaNode *tail;
    int size;
} Agenda;

// Functions provided for an Agenda
void init_agenda(Agenda *agenda);
void open_agenda(Agenda *agenda);
void close_agenda(Agenda *agenda);
void push_agenda(Agenda *agenda, AgendaItem **month);
void free_agenda(Agenda *agenda);
void print_agenda(Agenda *agenda);
int get_size_agenda(Agenda *agenda);
AgendaNode* search_node_agenda(Agenda *agenda, int month);

#endif