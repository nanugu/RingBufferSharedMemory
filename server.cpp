//export LD_LIBRARY_PATH=/home/nanugu/Downloads/boost_1_64_0/stage/lib:$LD_LIBRARY_PATH

#include <boost/lockfree/spsc_queue.hpp> // ring buffer
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <ctime>
#include <stdio.h>
#include <iostream>

namespace bip = boost::interprocess;
namespace shm
{

  typedef bip::allocator<int, bip::managed_shared_memory::segment_manager> char_alloc;
  
  typedef bip::basic_string<char, std::char_traits<char>, char_alloc >      shared_string;
  
  typedef boost::lockfree::spsc_queue<
    int, /*This is the variable, writing type data*/
    boost::lockfree::capacity<50>  > ring_buffer;
}

#include <unistd.h>
using namespace std;
#include <sys/time.h>
struct timeval start, stop, mid1, mid2;

int main()
{
  
  int i=0, k=0;
  int Data[10];    
  
  struct shm_remove{
    // create segment and corresponding allocator
     shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
    ~shm_remove() {bip::shared_memory_object::remove("MySharedMemory"); }
  }remover;
  
  
  // create segment and corresponding allocator
  bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
  shm::char_alloc char_alloc(segment.get_segment_manager());
  
  // Ringbuffer fully constructed in shared memory. The element strings are
  // also allocated from the same shared memory segment. This vector can be
  // safely accessed from other processes.
  
  
  shm::ring_buffer *queue = segment.find_or_construct<shm::ring_buffer>("queue")();
  
  i=0;
  while(1){    
    i++;
    
    for (k=0; k<10; k++) Data[k]=i;
    cout << "push=";
    for (k=0; k<10; k++)  cout << Data[k] << " ";
    cout << endl;
    queue->push(Data, 10);
    sleep(1);
  }

  return 0;
}

 
