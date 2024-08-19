#include <database.h>


void sendToDB(u32_t pressTimeMS) {
    GoogleFormPost gf;
    gf.setDebugMode(true);

    gf.setFormUrl(String(FORM_URL));

    gf.addData(String(FORM_DEVICE_CLASS), String(FORM_ID_CLASS)); // CLASS
    gf.addData(String(FORM_DEVICE_NAME), String(FORM_ID_NAME)); // DEVICE_NAME
    gf.addData(String(pressTimeMS), String(FORM_ID_PUSH_TIME)); //PUSH_TIME_MS

    gf.showDebug();
    gf.send();
}
