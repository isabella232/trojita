trojita_harmattan {
    CONFIG += mobility
    MOBILITY += systeminfo
    DEFINES += TROJITA_MOBILITY_SYSTEMINFO
}
macx:CONFIG += c++11

# common stuff
DEFINES -= QT3_SUPPORT
DEFINES += QT_STRICT_ITERATORS
