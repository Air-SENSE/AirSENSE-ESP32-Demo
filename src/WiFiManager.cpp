#include "WiFiManager.h"

ERROR_CODE WIFI_init()
{
#ifdef USING_WIFI_CONFIG

    WiFi.begin(ssid, pass);
    int retry_counter = 0;
    while (WiFi.status() != WL_CONNECTED && retry_counter <= 20) {
        delay(1000);
        retry_counter++;
    }
    if (WiFi.status() == wl_status_t::WL_CONNECTED)
    {
        log_e("WiFi connected!");
        log_e("IP: %s", WiFi.localIP().toString().c_str());
        connectionStatus_st.wifiStatus = status_et::CONNECTED;
        return ERROR_NONE;
    } else 
    {
        log_e("WiFi initialized failed!");
        connectionStatus_st.wifiStatus = status_et::DISCONNECTED;
        return ERROR_WIFI_INIT_FAILED;
    }
#endif
}