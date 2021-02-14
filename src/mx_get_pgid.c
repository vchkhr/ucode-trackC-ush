#include "ush.h"

int mx_get_pgid(t_shell *m_s, int job_id) {
    if (job_id > 10000 || m_s->jobs[job_id] == NULL) {
        return -1;
    }
    
    return m_s->jobs[job_id]->pgid;
}
