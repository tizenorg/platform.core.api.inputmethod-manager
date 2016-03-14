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
inputmethod_cynara_initialize ()
{
    int ret = cynara_initialize (&p_cynara, NULL);
    LOGW("[inputmethod_cynara_initialize]_check_privilege returned %d.", ret);
    return ret == CYNARA_API_SUCCESS;
}

void
inputmethod_cynara_finish ()
{
    if (p_cynara)
        cynara_finish (p_cynara);

    p_cynara = NULL;
}

bool
checkPrivilege (const char *uid, const char *privilege)
{
    if (!p_cynara){
        return false;
    }

    FILE *pFile = NULL;
    char smackLabel[1024] = "/proc/self/attr/current";
    pFile = fopen( "/proc/self/attr/current", "r" );
    if( pFile != NULL )
    {
        fread(smackLabel, sizeof(smackLabel), 1, pFile); 
        fclose( pFile );
    }
    LOGW("smackLabel = %s", smackLabel);

    pid_t pid = getpid();
    char* session =  cynara_session_from_pid(pid);
    LOGW("session = %s", session);

    int ret = cynara_check (p_cynara, smackLabel, session, uid, privilege);
    LOGW("[checkPrivilege]_check_privilege returned %d.", ret);
    free(session);
    if (ret != CYNARA_API_ACCESS_ALLOWED)
        return false;
    return true;
}
