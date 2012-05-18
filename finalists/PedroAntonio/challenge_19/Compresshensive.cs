/*
 * Tuenti Programming Challenge 2
 * Challenge 19: Find the Algorithm
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace Challenge19
{
	public class BitWriter
	{
		private Queue<uint> _buffer;
		private StringBuilder _builder;

		public BitWriter()
		{
			_buffer = new Queue<uint>();
			_builder = new StringBuilder();
		}

		public void Add( int v, int bits )
		{
			for ( int i = bits - 1; i >= 0; i-- )
			{
				uint bit = (uint) ( v >> i ) & 1;

				_buffer.Enqueue( bit );

				while ( _buffer.Count >= 8 )
					write();
			}
		}

		public override string ToString()
		{
			if ( _buffer.Count > 0 )
				write();

			return _builder.ToString();
		}

		private void write()
		{
			while ( _buffer.Count < 8 )
				_buffer.Enqueue( 0 );

			uint elem = 0;

			for ( int i = 0; i < 8; i++ )
			{
				elem = ( ( elem << 1 ) | _buffer.Dequeue() );
			}

			_builder.Append( elem.ToString( "x2" ) );
		}
	}

	public class Compresshensive
	{
		public static string ReadBase64Input( string input )
		{
			return ASCIIEncoding.ASCII.GetString( Convert.FromBase64String( input ) );
		}

		public static void PrintBase64Output( string output )
		{
			Console.WriteLine( Convert.ToBase64String( ASCIIEncoding.ASCII.GetBytes( output ) ).Replace( "=", "" ) );
		}

		private static int[] GetInputValues( String encoded )
		{
			String s = ReadBase64Input( encoded );

			int[] values = new int[s.Length / 8];
			for ( int i = 0; i < s.Length; i += 8 )
			{
				values[i / 8] = Convert.ToInt32( s.Substring( i, 8 ), 16 );
			}
			return values;
		}

		public static void Main( string[] args )
		{
			int[] values = GetInputValues( Console.ReadLine() );

			BitWriter writer = new BitWriter();

			int last = values[0];
			writer.Add( 1, 1 );
			writer.Add( last, 32 );

			for ( int i = 1; i < values.Length; i++ )
			{
				int v = values[i];
				int diff = v - last;

				if ( diff >= 16 || diff <= -17 )
				{
					writer.Add( 1, 1 );
					writer.Add( v, 32 );
				}
				else
				{
					writer.Add( 0, 1 );
					writer.Add( diff, 5 );
				}

				last = v;
			}

			PrintBase64Output( writer.ToString() );
		}
	}
}
