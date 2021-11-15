# The QT variable controls what modules are included in compilation.
# Note that the 'core' and 'gui' modules are included by default.
# For widget-based GUI applications, the 'widgets' module needs to be added.
QT += qml quick 

HEADERS = Window.h # Everything added to the HEADER variable will be checked 
                   # to see if moc needs to run on it, and it will be run if
                   # so.

SOURCES = main.cpp # Everything added to the SOURCES variable will be compiled
                   # and (in the simple example) added to the resulting
                   # executable.
