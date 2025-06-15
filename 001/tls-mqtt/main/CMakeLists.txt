# idf_component_register(SRCS "main.c" "wifi.c" "mqtt.c"
#                     INCLUDE_DIRS "."
#                     # EMBED_TXTFILES
#                     # "certs/ca.crt"
# )
# # Embed CA, client certificate, and private key
# target_add_binary_data(${COMPONENT_TARGET} "../certs/ca.crt"     TEXT)
# target_add_binary_data(${COMPONENT_TARGET} "../certs/client.crt" TEXT)
# target_add_binary_data(${COMPONENT_TARGET} "../certs/client.key" TEXT)

idf_component_register(SRCS "mqtt.c" "wifi.c" "main.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES 
                        "certs/ca.crt"
                        "certs/client.crt"
                        "certs/client.key")
