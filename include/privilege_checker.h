#ifndef __PRIVILEGE_CHECKER_H
#define __PRIVILEGE_CHECKER_H

#define IME_MANAGER_PRIVILEGE "http://tizen.org/privilege/imemanager"

bool inputmethod_cynara_initialize();
void inputmethod_cynara_finish();
bool checkPrivilege(const char *uid, const char *privilege);

#endif //__PRIVILEGE_CHECKER_H
