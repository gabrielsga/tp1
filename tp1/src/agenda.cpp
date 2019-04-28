#include "agenda.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>

// Initialize an empty agenda as a linked list with 12 month nodes.
// Each month node contains an array of appointment lists.
// The number of appointment lists for each month is the number days of that month.
void init_agenda(Agenda *agenda) {
    agenda->head = nullptr;
    agenda->tail = nullptr;
    agenda->size = 0;

    // Allocate 12 months in the agenda list
    for (int i = 1; i <= 12; i++) {
        AgendaItem *agenda_item = new AgendaItem;
        agenda_item->month = i;

        // Properly define the number of days in a month
        if (i == 2) {
            agenda_item->size = 28;
        }
        else if (i <= 7) {
            agenda_item->size = (i & 1) ? 31 : 30;
        }
        else {
            agenda_item->size = (i & 1) ? 30 : 31;
        }

        // Instantiate an array of appointment lists based on the number of days in a month
        agenda_item->appointment_list = new AppointmentList[agenda_item->size + 1];
        for (int j = 0; j <= agenda_item->size; j++) {
            init_appointment_list(&agenda_item->appointment_list[j]);
        }

        // Add the built month to the agenda
        push_agenda(agenda, &agenda_item);
    }
}

// Open an existing agenda from a file
void open_agenda(Agenda *agenda) {
    std::ifstream file;
    file.open(AGENDA_FILE_PATH);
    std::string line;

    while (getline(file, line)) { // Read line by line
        const int MONTH_FIELD  = 0;
        const int DAY_FIELD    = 1;
        const int HOUR_FIELD   = 2;
        const int MINUTE_FIELD = 3;
        const int DESCRIPTION_FIELD = 4;

        // Get each field of the line (each line is an appointment)
        std::istringstream ss(line);
        std::string token;
        std::string appointment_fields[5];
        int count = 0;
        while (getline(ss, token, AGENDA_DELIMITER)) {
            appointment_fields[count++] = token;
        }

        // Build up appointment
        int month, day;
        AppointmentItem *appointment = new AppointmentItem;
        std::istringstream(appointment_fields[MONTH_FIELD]) >> month;
        std::istringstream(appointment_fields[DAY_FIELD]) >> day;
        std::istringstream(appointment_fields[HOUR_FIELD]) >> appointment->hour;
        std::istringstream(appointment_fields[MINUTE_FIELD]) >> appointment->minute;
        appointment->description = appointment_fields[DESCRIPTION_FIELD];

        // Add appointment to the agenda
        AgendaNode *month_ptr = search_node_agenda(agenda, month);
        push_appointment(&month_ptr->item->appointment_list[day], &appointment);
    }
    file.close();
}

// Close the agenda by storing the appointments to a file
void close_agenda(Agenda *agenda) {
    std::ofstream file;
    file.open(AGENDA_FILE_PATH);

    // Iterate over every month of the agenda
    AgendaNode *ptr_agenda_node = agenda->head;
    while (ptr_agenda_node != nullptr) {
        AgendaItem *agenda_item = ptr_agenda_node->item;
        int month = agenda_item->month;
        int days = agenda_item->size;

        // For evey month, we get the appointment list for every day
        for (int i = 1; i <= days; i++) {
            AppointmentList appointments = agenda_item->appointment_list[i];
            AppointmentNode *ptr_appointment_node = appointments.head;

            // We then iterate over the appointment list of a day in the month
            // and store it to the file
            while (ptr_appointment_node != nullptr) {
                file << month << AGENDA_DELIMITER << i << AGENDA_DELIMITER
                     << ptr_appointment_node->item->hour << AGENDA_DELIMITER 
                     << ptr_appointment_node->item->minute << AGENDA_DELIMITER
                     << ptr_appointment_node->item->description << std::endl;
                ptr_appointment_node = ptr_appointment_node->next;
            }
        }
        ptr_agenda_node = ptr_agenda_node->next;
    }
    file.close();
}

// Add a month to the agenda
void push_agenda(Agenda *agenda, AgendaItem **month) {
    AgendaNode *new_node = new AgendaNode;
    new_node->item = *month;
    new_node->next = nullptr;

    // There is no month yet
    if (agenda->head == nullptr) {
        agenda->head = new_node;
        agenda->tail = new_node;
    }
    else {
        agenda->tail->next = new_node;
        agenda->tail = new_node;
    }
    agenda->size++;
}

// Free all the resources
void free_agenda(Agenda *agenda) {
    AgendaNode *ptr = agenda->head;
    while (ptr != nullptr) {
        //std::cout << "Month deleted: " << ptr->item->month << ", days: " << ptr->item->size << std::endl;
        AgendaNode *ptr_free = ptr;
        for (int i = 0; i <= ptr_free->item->size; i++) {
            free_appointment_list(&ptr_free->item->appointment_list[i]);
        }
        delete [] ptr_free->item->appointment_list;
        ptr = ptr->next;
        delete ptr_free->item;
        delete ptr_free;
    }
}

// Get the number of nodes (months, in this case)
int get_size_agenda(Agenda *agenda) {
    return agenda->size;
}

// Convert a month store as integer to string
std::string month_tostr(int month) {
    if (month < 1 || month > 12) {
        return "Invalid month.";
    }
    std::string months[13] = {"", "January", "February", "March", "April", "May", "June", "July", 
                              "August", "September", "October", "November", "December"};
    return months[month];
}

// Search for a node (month)
AgendaNode* search_node_agenda(Agenda *agenda, int month) {
    // Invalid month index
    if (month < 0 || month > agenda->size) {
        return nullptr;
    }

    // Iterate over the linked list and return the pointer to a node
    AgendaNode *ptr = agenda->head;
    while (ptr != nullptr && ptr->item->month != month) {
        ptr = ptr->next;
    }
    return ptr;
}
