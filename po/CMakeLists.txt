FIND_PACKAGE(Gettext REQUIRED)


IF (NOT GETTEXT_MSGMERGE_EXECUTABLE)
  MESSAGE(FATAL_ERROR "Please install msgmerge binary")
ENDIF (NOT GETTEXT_MSGMERGE_EXECUTABLE)

IF (NOT GETTEXT_MSGFMT_EXECUTABLE)
  MESSAGE(FATAL_ERROR "Please install msgmerge binary")
ENDIF (NOT GETTEXT_MSGFMT_EXECUTABLE)


FILE(GLOB pofiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.po)

GETTEXT_CREATE_TRANSLATIONS("krename.pot" "ALL" ${pofiles} )


