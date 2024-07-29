#include <database.h>


void sendToDB(u32_t pressTimeMS) {
    GoogleFormPost gf;
    gf.setDebugMode(true);

    gf.setFormUrl(String(FORM_URL));
    gf.addData(String("CLASS"), String(FORM_DEVICE_CLASS));
    gf.addData(String("DEVICE_NAME"), String(FORM_DEVICE_NAME));
    gf.addData(String("PUSH_TIME_MS"), String(pressTimeMS));

    gf.showDebug();
    gf.send();
}
