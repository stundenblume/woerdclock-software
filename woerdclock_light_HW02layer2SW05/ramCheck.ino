
//void ram_info() {  
// uint8_t *heapptr;
// uint8_t *stackptr;
//
// stackptr = (uint8_t *)malloc(4);   // use stackptr temporarily
// heapptr = stackptr;                // save value of heap pointer
// free(stackptr);                    // free up the memory again (sets stackptr to 0)
// stackptr =  (uint8_t *)(SP);       // save value of stack pointer
//#ifdef DEBUG
// Serial.print("HP: ");
// Serial.println((int) heapptr, HEX);
// Serial.print("SP: ");
// Serial.println((int) stackptr, HEX);
// Serial.print("Free: ");
// Serial.println((int) stackptr - (int) heapptr, HEX);
// Serial.println("");
//#endif
//}
