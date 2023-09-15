#include <SenseHat.h>
#include <menu.h>
// #undef KEY_DOWN
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#define MY_KEY_DOWN 258
#define MY_KEY_UP 259
#define MY_KEY_LEFT 260
#define MY_KEY_RIGHT 261
#define MY_ENTER_KEY 10
#include <fstream>
#include <vector>
#include <filesystem>
#include <ctime>
//SenseHat hat;


//Check if file exist - POSIX way
bool fileExistsMethod(const std::string& filename){
    return access(filename.c_str(), F_OK) != -1;
}

void writeSensorDataToCSV(const std::string& filename, const std::vector<float>& sensorData, const std::vector<const char*>& headerNames){
    std::ofstream csvFile;
    //bool fileExist = std::filesystem::exists(filename);
    bool fileExists = fileExistsMethod(filename);

    csvFile.open(filename, fileExists ? std::ios_base::app : std::ios_base::out);

    if(!csvFile.is_open()){
        std::cerr << "Failed to open file" << filename << std::endl;
        return;
    }
        //Get the current time
        time_t now = time(0);
        //Convert to localtime
        tm* localtm = localtime(&now);
        //A buffer to hold the time
        char timeBuffer[80];
        //Convert to a format that is not burger(murica)
        strftime(timeBuffer,80,"%d/%m/%Y %H:%M:%S",localtm);

    if(fileExists)
    {

        csvFile << timeBuffer;
        for (const auto& data : sensorData)
        {
            csvFile  << "," << data; 
        }
        csvFile << std::endl;
    }
    else{
        //Write the header
        csvFile << "Time";
        for (const auto& hName : headerNames)
        {
            csvFile << "," << hName;
        }
        //Endline
        csvFile << std::endl;
        
        csvFile << timeBuffer;
        for (const auto& data : sensorData)
        {
            csvFile  << "," << data; 
        }
        csvFile << std::endl;
    }
    
    csvFile.close();

}






SenseHat hat;
const char* get_additional_info(const char* item)
{
    float x,y,z;
    float aX,aY,aZ;
    float mX,mY,mZ;
    float pressure, temp, humidity;
    int angle;

    char *additional_info = new char[200];
    memset(additional_info, 0, sizeof(*additional_info));
    //char* additional_info = NULL;


    if (strcmp(item, "Pressure") == 0)
    {
        pressure = hat.GetPressure();

        snprintf(additional_info, 100, "%.10f", pressure);
        writeSensorDataToCSV("pressureData.csv", {pressure},{"Pressure"});
    }
    else if (strcmp(item, "Temperature") == 0)
    {
        temp = hat.GetTemperature();

        snprintf(additional_info, 100, "%.10f", temp);
        writeSensorDataToCSV("temperatureData.csv", {temp},{"Temperature"});

    }
    else if (strcmp(item, "Humidity") == 0)
    {
        humidity = hat.GetHumidity();

        snprintf(additional_info,100,"%.10f",humidity);
        writeSensorDataToCSV("humidityData.csv", {humidity}, {"Humidity"});
    }
    else if (strcmp(item, "Orientation") == 0)
    {
        hat.GetOrientation(x,y,z);
        if(x >= -360 && x <= 360 && y >= -360 && y <= 360 && z >= -360 && z <= 360)
            snprintf(additional_info,100,"%.10f, %.10f, %.10f",x,y,z);
            writeSensorDataToCSV("orientationData.csv", {x, y, z}, {"Pitch","Roll","Yaw"});
    }
    else if (strcmp(item, "Acceleration") == 0)
    {
        hat.GetAcceleration(aX,aY,aZ);
        if(aX >= -360 && aX <= 360 && aY >= -360 && aY <= 360 && aZ >= -360 && aZ <= 360)
            snprintf(additional_info,100,"%.10f, %.10f, %.10f",aX,aY,aZ);
            writeSensorDataToCSV("accelerationData.csv", {aX, aY, aZ}, {"X","Y","Z"});
    }
    else if (strcmp(item, "Magnometer") == 0)
    {
        hat.GetMagnetism(mX,mY,mZ);
        if(mX >= -360 && mX <= 360 && mY >= -360 && mY <= 360 && mZ >= -360 && mZ <= 360)
            snprintf(additional_info,100,"%.10f, %.10f, %.10f",mX,mY,mZ);
            writeSensorDataToCSV("magnometerData.csv", {mX, mY, mZ},{"X","Y","Z"});
    }
    return additional_info;
}


int main(void)
{
    const char *options[] = {
        "Pressure",
        "Temperature",
        "Humidity",
        "Orientation",
        "Acceleration",
        "Magnometer"
    };

    int i;
    int ch;
    MENU *menu;
    ITEM **items;
    WINDOW *w;
    WINDOW *popup_win;


    initscr();   /* initialize curses */
    curs_set(0); /* hide the blinking cursor */
    noecho();    /* hide the keyboard input */
    /* Create Items */
    items = (ITEM **)calloc(6, sizeof(ITEM *));
    for (i = 0; i < 6; i++)
    {
        items[i] = new_item(options[i], "");
    }

    /* Create Menu */
    menu = new_menu(items);
    
    /* Create Window for the menu */
    w = newwin(9, 15, 5, 5);
    box(w, 0, 0);
    keypad(w, TRUE);

    /* set menu window */
    set_menu_win(menu, w);

    /*set menu sub window */
    set_menu_sub(menu, derwin(w, 6, 14, 1, 1));
    set_menu_mark(menu, " "); /* string used as menu marker */

    /* set menu format - no of items to be displayed */
    set_menu_format(menu, 6, 1);
    popup_win = newwin(10, 50, 5, 25);


    /*post the menu */
    post_menu(menu);
    wrefresh(w);

    while ((ch = wgetch(w)) != 27)
    {
        // printf("%d\n",ch);
        switch (ch)
        {
        case MY_KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case MY_KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
        case KEY_NPAGE:
            menu_driver(menu, REQ_SCR_DPAGE);
            break;
        case KEY_PPAGE:
            menu_driver(menu, REQ_SCR_UPAGE);
            break;
        case MY_ENTER_KEY:
            if (current_item(menu) != NULL) {
                const char *item_name_str = item_name(current_item(menu));  
                              // Retrieve additional information based on the selected menu item
                                werase(popup_win);
                const char *additional_info = get_additional_info(item_name_str);

                // Clear the popup window
                werase(popup_win);

                // Display the additional information in the popup window
                mvwprintw(popup_win, 1, 1, "Additional Information:");
                mvwprintw(popup_win, 3, 1, "%s", additional_info);

                // Refresh and display the popup window
                wrefresh(popup_win);
                //Clean up
                delete[] additional_info;
            }
        }
    }
    unpost_menu(menu);
    delwin(popup_win);
    free_menu(menu);
    for (i = 0; i < 6; i++)
    {
        free_item(items[i]);
    }
    endwin();
    return 0;
}


