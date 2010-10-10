z_stream z;
char input_buffer[ 1024 ];
char output_buffer[ 1024 ];
FILE *fin;
FILE *fout;
int status;
/*
 * Setup code for your specific problem
 */
z.avail_in = 0;
z.next_out = output_buffer;
z.avail_out = 1024;
for ( ; ; ) 
{
  if ( z.avail_in == 0 ) 
  {
    z.next_in = input_buffer;
    z.avail_in = fread( input_buffer, 1, 1024, fin );
  }
  if ( z.avail_in == 0 )
  {
    break;
  }
  status = deflate( &z, Z_NO_FLUSH );
  int count = 1024 - z.avail_out;
  if ( count )
  {
   fwrite ( output_buffer, 1, count, fout );
  }
  z.next_out = output_buffer;
  z.avail_out = 1024;
}
}

