program saxpy
 use omp_lib
 implicit none
 integer :: i,n, chunk
 real,dimension(:), allocatable :: x, y
 real :: a,start_time, end_time
 a = 2.0d0
 n = 512*512*512
 chunk  = 16
 allocate(x(n),y(n))

! Parallelize this block of code (optional)
!$omp parallel do
 do i = 1, n
  x(i) = 1.0d0
  y(i) = 2.0d0
 end do
 
 call cpu_time(start_time)
 !$omp parallel do schedule(static, chunk)
 do i = 1, N
  y(i) = y(i) + a * x(i) 
 end do
 !$omp end parallel do 
 call cpu_time(end_time)

 print '(a,f8.6)', 'SAXPY Time: ', end_time - start_time

 do i = 1, 5
   print *, y(i)
 end do

 deallocate(x,y)
end program saxpy
