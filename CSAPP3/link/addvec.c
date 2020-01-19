/* addvec.c */
/* $begin addvec */
int addcnt = 0;

void addvec(int *x, int *y,
	    int *z, int n) 
{
    int i;

    addcnt++;

    for (i = 0; i < n; i++)
	z[i] = x[i] + y[i];
}

/*   added by alex, used in page 724, figure 7.8 */
void vec()
{
	int j;
	j++;

}

/* $end addvec */

