/*
 * YaST2: Core system
 *
 * Description:
 *   YaST2 SCR: PPD implementation
 *
 * Authors:
 *   Michal Svec <msvec@suse.cz>
 *
 * $Id$
 */

#ifndef _PPD_h
#define _PPD_h

#include <sys/types.h>

#include <string>
#include <list>
#include <map>

using namespace std;

#define MAX        2048
#define WHITESPACE " \t\n"

#define PPD_DIR "/usr/share/cups/model"
#define PPD_DB  "/var/lib/YaST2/ppd_db.ycp"

class PPD {
    public:

        /* typedef string Info; */
        class Info {
            public:
                string filename;
                string pnp_vendor;
                string pnp_printer;
        };

        class PPDInfo {
            public:
                string filename;
                string vendor;
                string printer;
                string product;
                string nick;
                string lang;
                string pnp_vendor;
                string pnp_printer;
        };

        typedef string Vendor;
        typedef string Model;
        typedef string Driver;
        typedef map<Driver,Info> Drivers;
        typedef map<Model,Drivers> Models;
        typedef map<Vendor,Models> Vendors;

        PPD(const char *ppddir = PPD_DIR, const char *ppddb = PPD_DB);
        ~PPD();

        bool createdb();
        bool changed(int *count);
	bool fileinfo(const char *file, PPDInfo *info);

    private:
        Vendors db;
        char ppd_dir[MAX];
        char ppd_db[MAX];
        time_t mtime;

        typedef map<string,string> VendorsMap;
        VendorsMap vendors_map;

        bool mtimes(const char *dirname, time_t mtime, int *count);
        bool process_dir(const char *dirname);
        bool process_file(const char *filename, PPDInfo *newinfo = NULL);
        void preprocess(PPDInfo info, PPDInfo *newinfo);
        void debugdb() const;

    protected:
        string strupper(const string s);
        string killchars(const string s, const string chr);
        string killspaces(const string s);
        string killbraces(const string s);
        string addbrace(const string s);
        string first(const string s, const string sep = " -/");
        string clean(const char *s);
};

#endif /* _PPD_h */
