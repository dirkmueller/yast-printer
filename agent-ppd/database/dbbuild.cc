/*
   File:       runag_rcconfig.cc

   Author:     Jiri Srain    <jsrain@suse.cz>

/-*/

#include <stdio.h>
#include <unistd.h>
#include <utime.h>

#define Y2LOG "dbbuild"

#include "../src/PPDAgent.h"

int
main (int argc, char *argv[])
{

    setenv("Y2_PRINTER_DATA_DIR", "../../data/", 1);
    PPD ppd;
    ppd.createdbThread ("ppd_db.ycp");
    return 0;
}