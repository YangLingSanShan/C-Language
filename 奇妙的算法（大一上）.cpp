#define read(a) {char c;while((c=getchar())>47) a=a*10+(c^48);}        //宏函数快读
void isPrime(int n,int is_prime[])//埃氏筛，将is_prime中下表为素数的位置映射为1，合数为0
{
    for (int i = 2;i < n;i++)
        is_prime[i] = 1;
    for (int i = 2;i * i < n;i++)
    {
        if (is_prime[i] == 1)
            for (int j = i * i;j < n;j += i)
                is_prime[j] = 0;
    }
}
/*优化：欧氏筛
int prime[N], cnt, notPrime[N + 1]; // 意义同上:全标记为0（质数）
for (int i = 2; i < N; i++)
{
    if (!notPrime[i]) prime[cnt++] = i; // 记录素数
    for (int j = 0; j < cnt && prime[j] <= n / i; j++) // j 是一个编号而已，prime[j] 才是上文说的 p
    {
        not_prime[i * prime[j]] = 1; // 筛掉
        if (i % prime[j] == 0) break; // 如果 prime[j] | i，说明这是 i 的最小质因子，更大的素数就不需要了
    }
}
*/
long long Sum_One(long long target)//统计 target中1的个数
{
    long long sum = target;
    sum = (sum & 0x5555555555555555) + ((sum >> 1) & 0x5555555555555555);
    sum = (sum & 0x3333333333333333) + ((sum >> 2) & 0x3333333333333333);
    sum = (sum & 0x0F0F0F0F0F0F0F0F) + ((sum >> 4) & 0x0F0F0F0F0F0F0F0F);
    sum = (sum * (0x0101010101010101) >> 56);
    return sum;
}
/*位运算的妙用
* 1.（a+b）>>1来求俩个无符号数（正数和0）的平均数
* 2. y=(1<<a)|(1<<b)|(1<<c); //得到一个第a,b,c位都是1的数
*    x=x|y;//把x的a,b,c位设置为1
* 3. x=~(1<<d)&x; //把x的第d位设置为-0
* 4. n&(n-1)//作用：将n的二进制表示中的最低位为1的改为0,这一作用可以拓展到很多用法，比如计算二进制数中1的个数，计算N！的质因数2的个数
* 5. n > 0 && ((n & (n - 1)) == 0 ) //判断一个数是否是2的方幂
* 6. n&(-n) //表示将一个数只是保留二进制下最右边的1的位
*/


/*快速幂
*#include <stdio.h>
long long fastPower(long long base, long long power,long long p) 
{
    long long result = 1;
    while (power > 0) {
        if (power & 1) 
        {
            result = result * base % p;
        }
        power >>= 1;
        base = (base * base) % p;
    }
    return result;
}
int main()
{
    long long a, b, p;
    scanf("%lld%lld%lld", &a, &b, &p);
    printf("%lld", fastPower(a, b, p));
}
*/
/*
 多组数据【你不知道有多少组输入，也没有明显的输入结束的标志】输入时，可以使用以下代码：
int n;
while (scanf("%d", &n) != EOF){
    // do something
}
该代码表示，不停执行 scanf("%d", &n) ，直到到达文件末尾(EOF, End Of File)。在Windows下执行此代码，输入结束时，可以按下Ctr + Z并输入一个回车，为程序提供“到达文件末尾”信号，使程序跳出该while循环从而正常结束。
*/