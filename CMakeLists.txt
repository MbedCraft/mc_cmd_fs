idf_component_register(SRCS "mc_cmd_fs.c"
                    INCLUDE_DIRS .
                    PRIV_REQUIRES
                        console
                        mc_assert
                        mc_fs)
