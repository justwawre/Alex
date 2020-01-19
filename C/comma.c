/* precedence of operator comma  */

int main() {
  int i;
  i = 2, 3;           //assignment has higher precedence tha comma operation
  int j= (2, 3);
  int k = ({3;4;});
  /* here i==2  j==3 ,k==4 */
  return 0;
}