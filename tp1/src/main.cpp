#include "appointment.hpp"
#include "agenda.hpp"
#include <iostream>
#include <cstring>

#define OPEN_AGENDA       1
#define ADD_APPOINTMENT   2
#define DEL_APPOINTMENT   3
#define LIST_APPOINTMENTS 4
#define CHECK_APPOINTMENT 5
#define CLOSE_AGENDA      6
#define EXIT              7

// Pop a menu to guide the user. The available options are showin below (1 - 6)
int choose_menu() {
    bool valid_option = false;
    int option;
    
    // Keep popping up the menu until a valid option is selected
    while (!valid_option) {
        std::cout << "----------------------------------------------------" << std::endl
                  << "                    . : MENU : .                    " << std::endl
                  << "----------------------------------------------------" << std::endl
                  << "1 - Open agenda"         << std::endl
                  << "2 - Add appointment"     << std::endl
                  << "3 - Delete appointment"  << std::endl
                  << "4 - List appointments"   << std::endl
                  << "5 - Check appointement"  << std::endl 
                  << "6 - Close agenda"        << std::endl 
                  << "7 - Exit without saving" << std::endl
                  << "----------------------------------------------------" << std::endl;
        std::cout << "Choose your option: ";
        std::cin >> option;
        valid_option = (option > 0 && option < 8);
        if (!valid_option) {
            std::cout << "Invalid option. Try again!" << std::endl << std::endl;
        }
    }
    return option;
}

// Search and return an appointment list based on month and day
AppointmentList* get_appointment(Agenda *agenda, int month, int day) {
    if (month < 1 || month > 12) {
        std::cout << "Invalid month." << std::endl;
        return nullptr;
    }
    AgendaNode *month_ptr = search_node_agenda(agenda, month);
    if (day < 1 || day > month_ptr->item->size) {
        std::cout << "Invalid day for selected month." << std::endl;
        return nullptr;
    }
    return &month_ptr->item->appointment_list[day];
}

int main() {
    Agenda agenda;
    init_agenda(&agenda);

    int option = 0;
    bool is_agenda_opened = false;
    while (option != CLOSE_AGENDA && option != EXIT) {
        option = choose_menu();

        if (option == OPEN_AGENDA) { // Open agenda from file
            if (is_agenda_opened) {
                std::cout << "The agenda has already been opened." << std::endl;
            }
            else {
                open_agenda(&agenda);
                std::cout << "The agenda has been opened." << std::endl;
                is_agenda_opened = true;
            }
        }
        else if (option == ADD_APPOINTMENT) { // Add an appointment
            if (!is_agenda_opened) {
                std::cout << "You must open the agenda before any operation." << std::endl;
                continue;
            }
            int month, day;
            std::cout << "Enter the month: ";
            std::cin >> month;
            std::cout << "Enter the day: ";
            std::cin >> day;
            
            // Get appointment list according to the month and day selected
            AppointmentList *appointment_list = get_appointment(&agenda, month, day);
            if (appointment_list == nullptr) {
                continue; // Skipping due to invalid input
            }

            // Build up the appointment
            AppointmentItem *appointment = new AppointmentItem;
            std::cout << "Hour: ";
            std::cin >> appointment->hour;
            std::cout << "Minute: ";
            std::cin >> appointment->minute;
            std::cout << "Description: ";
            std::cin.ignore(2, '\n');
            std::getline(std::cin, appointment->description);

            // Add appointment to the agenda
            push_appointment(appointment_list, &appointment);
        }
        else if (option == DEL_APPOINTMENT) { // Delete an appointment
            if (!is_agenda_opened) {
                std::cout << "You must open the agenda before any operation." << std::endl;
                continue;
            }
            int month, day;
            std::cout << "Enter the month: ";
            std::cin >> month;
            std::cout << "Enter the day: ";
            std::cin >> day;
            
            // Get appointment list according to the month and day selected
            AppointmentList *appointment_list = get_appointment(&agenda, month, day);
            if (appointment_list == nullptr) {
                continue; // Skipping due to invalid input
            }

            int hour, minute;
            std::cout << "Hour: ";
            std::cin >> hour;
            std::cout << "Minute: ";
            std::cin >> minute;
            std::cout << std::endl;
            // Delete appointment from the agenda
            if (delete_appointment(appointment_list, hour, minute)) {
                std::cout << "The appointment has been deleted." << std::endl;
            }
            else {
                std::cout << "There is no such appointment." << std::endl;
            }
        }
        else if (option == LIST_APPOINTMENTS) { // List appointments based on month and day
            if (!is_agenda_opened) {
                std::cout << "You must open the agenda before any operation." << std::endl;
                continue;
            }
            int month, day;
            std::cout << "Enter the month: ";
            std::cin >> month;        
            std::cout << "Enter the day: ";
            std::cin >> day;
            std::cout << std::endl;

            // Get appointment list according to the month and day selected
            AppointmentList *appointment_list = get_appointment(&agenda, month, day);
            if (appointment_list == nullptr) {
                continue; // Skipping due to invalid input
            }

            // Print all appointments scheduled for a day in a month
            if (is_empty_appointment_list(appointment_list)) {
               std::cout << "There is no appointment scheduled for this date." << std::endl;
            }
            else {
                print_appointment_list(appointment_list);
            }
        }
        else if (option == CHECK_APPOINTMENT) { // Check whether there is an appoint for a date
            if (!is_agenda_opened) {
                std::cout << "You must open the agenda before any operation." << std::endl;
                continue;
            }
            int month, day;
            std::cout << "Enter the month: ";
            std::cin >> month;        
            std::cout << "Enter the day: ";
            std::cin >> day;
            std::cout << std::endl;

            // Get appointment list according to the month and day selected
            AppointmentList *appointment_list = get_appointment(&agenda, month, day);
            if (appointment_list == nullptr) {
                continue; // Skipping due to invalid input
            }

            int hour, minute;
            std::cout << "Hour: ";
            std::cin >> hour;
            std::cout << "Minute: ";
            std::cin >> minute;
            std::cout << std::endl;

            // Print all appointments scheduled for a day in a month
            if (is_empty_appointment_list(appointment_list)) {
               std::cout << "There is no appointment scheduled for this date." << std::endl;
            }
            else {
                int num_appointments = print_appointment_list_by_date(appointment_list, hour, minute);
                if (num_appointments == 0) {
                    std::cout << "There is no appointment scheduled for this date." << std::endl;
                }
            }
        }
        else if (option == CLOSE_AGENDA) { // Close the agenda
            if (!is_agenda_opened) {
                std::cout << "There is no open agenda to close. Exitting program." << std::endl;
                break;
            }

            // Close the agenda and save appointments to file
            std::cout << "Closing agenda and storing current status on disk." << std::endl;
            close_agenda(&agenda);
        }
        else if (option == EXIT) {
            std::cout << "Exitting. All changes will be lost." << std::endl;
        }
    }
    free_agenda(&agenda);
    return 0;
}
