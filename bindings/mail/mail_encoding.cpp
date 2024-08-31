#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <SupportDefs.h>
#include <mail/mail_encoding.h>
/*
#include <ctype.h>
#include <string.h>
#include <strings.h>*/

namespace py = pybind11;
/* source mail_encoding.cpp from mail-kit
#define	DEC(c) (((c) - ' ') & 077)

static const char kHexAlphabet[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
	'8','9','A','B','C','D','E','F'};

ssize_t encode_qp_wrapper(char *out, const char *in, off_t length, int headerMode)
{
	int g = 0, i = 0;

	for (; i < length; i++) {
		if (((uint8 *)(in))[i] > 127 || in[i] == '?' || in[i] == '='
			|| in[i] == '_'
			// Also encode the letter F in "From " at the start of the line,
			// which Unix systems use to mark the start of messages in their
			// mbox files.
			|| (in[i] == 'F' && i + 5 <= length && (i == 0 || in[i - 1] == '\n')
				&& in[i + 1] == 'r' && in[i + 2] == 'o' && in[i + 3] == 'm'
				&& in[i + 4] == ' ')) {
			out[g++] = '=';
			out[g++] = kHexAlphabet[(in[i] >> 4) & 0x0f];
			out[g++] = kHexAlphabet[in[i] & 0x0f];
		} else if (headerMode && (in[i] == ' ' || in[i] == '\t')) {
			out[g++] = '_';
		} else if (headerMode && in[i] >= 0 && in[i] < 32) {
			// Control codes in headers need to be sanitized, otherwise certain
			// Japanese ISPs mangle the headers badly.  But they don't mangle
			// the body.
			out[g++] = '=';
			out[g++] = kHexAlphabet[(in[i] >> 4) & 0x0f];
			out[g++] = kHexAlphabet[in[i] & 0x0f];
		} else
			out[g++] = in[i];
	}

	return g;
}

ssize_t decode_qp_wrapper(char *out, const char *in, off_t length, int underscoreIsSpace)
{
	// decode Quoted Printable
	char *dataout = out;
	const char *datain = in, *dataend = in + length;

	while (datain < dataend) {
		if (*datain == '=' && dataend - datain > 2) {
			int a = toupper(datain[1]);
			a -= a >= '0' && a <= '9' ? '0' : (a >= 'A' && a <= 'F'
				? 'A' - 10 : a + 1);

			int b = toupper(datain[2]);
			b -= b >= '0' && b <= '9' ? '0' : (b >= 'A' && b <= 'F'
				? 'A' - 10 : b + 1);

			if (a >= 0 && b >= 0) {
				*dataout++ = (a << 4) + b;
				datain += 3;
				continue;
			} else if (datain[1] == '\r' && datain[2] == '\n') {
				// strip =<CR><NL>
				datain += 3;
				continue;
			}
		} else if (*datain == '_' && underscoreIsSpace) {
			*dataout++ = ' ';
			++datain;
			continue;
		}

		*dataout++ = *datain++;
	}

	*dataout = '\0';
	return dataout - out;
}

ssize_t encode_wrapper(mail_encoding encoding, char *out, const char *in, off_t length, int headerMode)
{
	switch (encoding) {
		case base64:
			return encode_base64(out,in,length,headerMode);
		case quoted_printable:
			return encode_qp(out,in,length,headerMode);
		case seven_bit:
		case eight_bit:
		case no_encoding:
			memcpy(out,in,length);
			return length;
		case uuencode:
		default:
			return -1;
	}

	return -1;
}

ssize_t decode_wrapper(mail_encoding encoding, char *out, const char *in, off_t length, int underscoreIsSpace)
{
	switch (encoding) {
		case base64:
			return decode_base64(out, in, length);
		case uuencode:
			return uu_decode(out, in, length);
		case seven_bit:
		case eight_bit:
		case no_encoding:
			memcpy(out, in, length);
			return length;
		case quoted_printable:
			return decode_qp(out, in, length, underscoreIsSpace);
		default:
			break;
	}

	return -1;
}

mail_encoding encoding_for_cte_wrapper(const char *cte)
{
	if (cte == NULL)
		return no_encoding;

	if (strcasecmp(cte,"uuencode") == 0)
		return uuencode;
	if (strcasecmp(cte,"base64") == 0)
		return base64;
	if (strcasecmp(cte,"quoted-printable") == 0)
		return quoted_printable;
	if (strcasecmp(cte,"7bit") == 0)
		return seven_bit;
	if (strcasecmp(cte,"8bit") == 0)
		return eight_bit;

	return no_encoding;
}

ssize_t max_encoded_length_wrapper(mail_encoding encoding, off_t length)
{
	switch (encoding) {
		case base64:
		{
			double result = length * 1.33333333333333;
			result += (result / BASE64_LINELENGTH) * 2 + 20;
			return (ssize_t)(result);
		}
		case quoted_printable:
			return length * 3;
		case seven_bit:
		case eight_bit:
		case no_encoding:
			return length;
		case uuencode:
		default:
			return -1;
	}

	return -1;
}

ssize_t uu_decode_wrapper(char *out, const char *in, off_t length)
{
	long n;
	uint8 *p, *inBuffer = (uint8 *)in;
	uint8 *outBuffer = (uint8 *)out;

	inBuffer = (uint8 *)strstr((char *)inBuffer, "begin");
	goto enterLoop;

	while ((inBuffer - (uint8 *)in) <= length
		&& strncmp((char *)inBuffer, "end", 3)) {
		p = inBuffer;
		n = DEC(inBuffer[0]);

		for (++inBuffer; n > 0; inBuffer += 4, n -= 3) {
			if (n >= 3) {
				*outBuffer++ = DEC(inBuffer[0]) << 2 | DEC (inBuffer[1]) >> 4;
				*outBuffer++ = DEC(inBuffer[1]) << 4 | DEC (inBuffer[2]) >> 2;
				*outBuffer++ = DEC(inBuffer[2]) << 6 | DEC (inBuffer[3]);
			} else {
				if (n >= 1) {
					*outBuffer++ = DEC(inBuffer[0]) << 2
						| DEC (inBuffer[1]) >> 4;
				}
				if (n >= 2) {
					*outBuffer++ = DEC(inBuffer[1]) << 4
						| DEC (inBuffer[2]) >> 2;
				}
			}
		}
		inBuffer = p;

	enterLoop:
		while (inBuffer[0] != '\n' && inBuffer[0] != '\r' && inBuffer[0] != 0)
			inBuffer++;
		while (inBuffer[0] == '\n' || inBuffer[0] == '\r')
			inBuffer++;
	}

	return (ssize_t)(outBuffer - (uint8 *)in);
}*/

PYBIND11_MODULE(mail_encoding, m)
{
py::enum_<mail_encoding>(m, "mail_encoding", "")
.value("base64", mail_encoding::base64, "")
.value("quoted_printable", mail_encoding::quoted_printable, "")
.value("seven_bit", mail_encoding::seven_bit, "")
.value("eight_bit", mail_encoding::eight_bit, "")
.value("uuencode", mail_encoding::uuencode, "")
.value("null_encoding", mail_encoding::null_encoding, "")
.value("no_encoding", mail_encoding::no_encoding, "")
.export_values();
/*
m.def("encode", &encode_wrapper, "", py::arg("encoding"), py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode", &decode_wrapper, "", py::arg("encoding"), py::arg("out"), py::arg("in"), py::arg("length"), py::arg("underscore_is_space"));

m.def("max_encoded_length", &max_encoded_length_wrapper, "", py::arg("encoding"), py::arg("cur_length"));

m.def("encoding_for_cte", &encoding_for_cte_wrapper, "", py::arg("content_transfer_encoding"));

m.def("encode_base64", &encode_base64, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode_base64", &decode_base64, "", py::arg("out"), py::arg("in"), py::arg("length"));

m.def("encode_qp", &encode_qp_wrapper, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode_qp", &decode_qp_wrapper, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("underscore_is_space"));

m.def("uu_decode", &uu_decode_wrapper, "", py::arg("out"), py::arg("in"), py::arg("length"));
*/

m.def("encode", &encode, "", py::arg("encoding"), py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode", &decode, "", py::arg("encoding"), py::arg("out"), py::arg("in"), py::arg("length"), py::arg("underscore_is_space"));

m.def("max_encoded_length", &max_encoded_length, "", py::arg("encoding"), py::arg("cur_length"));

m.def("encoding_for_cte", &encoding_for_cte, "", py::arg("content_transfer_encoding"));

m.def("encode_base64", &encode_base64, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode_base64", &decode_base64, "", py::arg("out"), py::arg("in"), py::arg("length"));

m.def("encode_qp", &encode_qp, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode_qp", &decode_qp, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("underscore_is_space"));

m.def("uu_decode", &uu_decode, "", py::arg("out"), py::arg("in"), py::arg("length"));

}
