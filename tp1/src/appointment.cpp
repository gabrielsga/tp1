#include "appointment.hpp"
#include <iomanip>

// Initialize an appointment list
void init_appointment_list(AppointmentList *appointment_list) {
    appointment_list->head = nullptr;
    appointment_list->tail = nullptr;
    appointment_list->size = 0;
}

// Free resources
void free_appointment_list(AppointmentList *appointment_list) {
    AppointmentNode *ptr = appointment_list->head;
    while (ptr != nullptr) {
        AppointmentNode *ptr_free = ptr;
        ptr = ptr->next;
        delete ptr_free->item;
        delete ptr_free;
    }
}

// Add an appointment item to an appointment list
void push_appointment(AppointmentList *appointment_list, AppointmentItem **item) {
    AppointmentNode *new_node = new AppointmentNode;
    new_node->item = *item;
    new_node->next = nullptr;

    // The list is empty
    if (appointment_list->head == nullptr) {
        appointment_list->head = new_node;
        appointment_list->tail = new_node;
    }
    else {
        appointment_list->tail->next = new_node;
        appointment_list->tail = new_node;
    }
    appointment_list->size++;
}

// Delete an appointment from the list
bool delete_appointment(AppointmentList *appointment, int hour, int minute) {
    AppointmentNode *curr_ptr = appointment->head;
    AppointmentNode *prev_ptr = appointment->head;

    // Iterate over the linked list
    while (curr_ptr != nullptr) {
        // Have we found the node we're looking for? If so, we delete it
        if (curr_ptr->item->hour == hour && curr_ptr->item->minute == minute) {
            if (curr_ptr == appointment->head) { // It's the first node
                appointment->head = curr_ptr->next;
            }
            else { // It's somewhere else in the list (middle or end point)
                prev_ptr->next = curr_ptr->next;
            }
            //node_deleted = true;
            delete curr_ptr->item;
            delete curr_ptr;
            appointment->size--;
            return true;
        }
        prev_ptr = curr_ptr;
        curr_ptr = curr_ptr->next;
    }
    return false;
}

// Check whether an appointment list is empty
bool is_empty_appointment_list(AppointmentList *appointment_list) {
    return appointment_list->size == 0;
}

// Get the size of an appointment list
int get_size_appointment_list(AppointmentList *appointment_list) {
    return appointment_list->size;
}

// Print all the appointments of a list
void print_appointment_list(AppointmentList *appointment_list) {
    AppointmentNode *ptr = appointment_list->head;
    while (ptr != nullptr) {
        std::cout << "At " << std::setw(2) << std::setfill('0') << ptr->item->hour << ":" 
                  << std::setw(2) << std::setfill('0') << ptr->item->minute 
                  << ": " << ptr->item->description << std::endl;
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

int print_appointment_list_by_date(AppointmentList *appointment_list, int hour, int minute) {
    int count = 0;
    AppointmentNode *ptr = appointment_list->head;
    while (ptr != nullptr) {
        if (ptr->item->hour == hour && ptr->item->minute == minute) {
            std::cout << "At " << std::setw(2) << std::setfill('0') << ptr->item->hour << ":" 
                    << std::setw(2) << std::setfill('0') << ptr->item->minute 
                    << ": " << ptr->item->description << std::endl;
            count++;
        }
        ptr = ptr->next;
    }
    std::cout << std::endl;
    return count;
}