#include "privilege_checker.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlog.h>
#include <unistd.h>

#include <cynara-client.h>
#include <cynara-error.h>
#include <cynara-creds-socket.h>
#include <cynara-session.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "INPUTMETHOD_MANAGER"

namespace
{

cynara *p_cynara = NULL;

}

bool
inputmethod_cynara_initialize()
{
    int ret = cynara_initialize (&p_cynara, NULL);
    LOGW("[inputmethod_cynara_initialize]_check_privilege returned %d.", ret);
    return ret == CYNARA_API_SUCCESS;
}

void
inputmethod_cynara_finish()
{
    if (p_cynara)
        cynara_finish (p_cynara);

    p_cynara = NULL;
}

bool
checkPrivilege(const char *uid, const char *privilege)
{
    if (!p_cynara) {
        return false;
    }

    FILE *file = NULL;
    char smackLabel[1024] = "/proc/self/attr/current";
    file = fopen( "/proc/self/attr/current", "r" );
    if (file != NULL) {
        int icount = fread(smackLabel, 1, sizeof(smackLabel), file);
        if (icount < 0) {
            LOGW("Error : fread");
        }
        fclose(file);
    }

    pid_t pid = getpid();
    char *session = cynara_session_from_pid(pid);
    int ret = cynara_check(p_cynara, smackLabel, session, uid, privilege);
    LOGW("[checkPrivilege]_check_privilege returned %d.", ret);
    if (ret != CYNARA_API_ACCESS_ALLOWED)
        return false;
    return true;
}
