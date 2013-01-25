if( PTB_NO_MANPAGES )
  message("Ignoring manpages, on user's demand.")
else( PTB_NO_MANPAGES )
  if(DOCBOOK_TO_MAN_FOUND)
    docbook_create_man( ptb-man 6 plee-the-bear.sgml )
  else(DOCBOOK_TO_MAN_FOUND)
    message("docbook-to-man was not found on your system. The manpages of "
      "Plee the Bear are not generated.")
  endif(DOCBOOK_TO_MAN_FOUND)
endif( PTB_NO_MANPAGES )

