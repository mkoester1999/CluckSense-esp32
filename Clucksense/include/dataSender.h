#pragma once
    #include <Arduino.h>
    #include "dataSender.cpp"

    /*Returns an 8 character alphanumeric uuid from the db*/
    String getUUID();
    /*sends data to the server*/
    void sendData(int, int, bool, bool);
