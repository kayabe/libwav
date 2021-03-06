#ifndef __WAV_H__
#define __WAV_H__

/**
 * Simple PCM wav file I/O library
 *
 * Author: Zhaosheng Pan <zhaosheng.pan@sololand.moe>
 *
 * The API is designed to be similar to stdio.
 *
 * This library does not support:
 *  - formats other than PCM, IEEE float and log-PCM
 *  - extra chunks after the data chunk
 *  - big endian platforms (might be supported in the future)
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "wav_defs.h"
#include <stddef.h>
#include <stdint.h>

/** function:       wave_open
 *  description:    Open a wave file
 *  parameters:
 *      filename:   The name of the wave file
 *      mode:       The mode for open (same as fopen)
 *  return:         NULL if the memory allocation for the WaveFile object failed.
 *                  Non-NULL means the memory allocation succeeded, but there can be other errors,
 *                  which can be got using wav_errno or wave_error.
 */
WavFile* wav_open(char* filename, char* mode);
int      wav_close(WavFile* wave);
WavFile* wav_reopen(char* filename, char* mode, WavFile* wave);

/** function:       wave_read
 *  description:    Read a block of samples from the wave file
 *  parameters:
 *      buffers:    A list of pointers to a buffer where the data of each single channel will be placed
 *      count:      The number of frames (block size)
 *      wave:       The pointer to the WaveFile structure
 *  return:         The number of frames read
 *                  If returned value < {count}, either EOF reached or an error occured
 *  remarks:        This API does not support extensible format.
 *                  For extensible format, use {wave_read_raw} instead.
 */
size_t wav_read(void** buffers, size_t count, WavFile* wave);

/** function:       wave_write
 *  description:    Write a block of samples to the wave file
 *  parameters:
 *      buffers:    A list of pointers to a buffer of the data of a single channel.
 *      count:      The number of frames (block size)
 *      wave:       The pointer to the WaveFile structure
 *  return:         The number of frames written
 *                  If returned value < {count}, either EOF reached or an error occured.
 *  remarks:        This API does not support extensible format.
 *                  For extensible format, use {wave_read_raw} instead.
 */
size_t wav_write(void** buffers, size_t count, WavFile* wave);

/** function:       wave_tell
 *  description:    Tell the current position in the wave file.
 *  parameters:
 *      wave:       The pointer to the WaveFile structure.
 *  return:         The current frame number.
 */
long int wav_tell(WavFile* wave);

int  wav_seek(WavFile* wave, long int offset, int origin);
void wav_rewind(WavFile* wave);

/** function:       wave_eof
 *  description:    Tell if the end of the wave file is reached.
 *  parameters:
 *      wave:       The pointer to the WaveFile structure.
 *  return:         Non-zero integer if the end of the wave file is reached,
 *                  otherwise zero.
 */
int wav_eof(WavFile* wave);

/** function:       wave_error
 *  description:    Tell if an error occurred in the last operation
 *  parameters:
 *      wave:       The pointer to the WaveFile structure
 *  return:         Non-zero if there is an error, otherwise zero
 */
int wav_error(WavFile* wave);

int wav_flush(WavFile* wave);

/** function:       wav_errno
 *  description:    Get the error code of the last operation.
 *  parameters:
 *      self        The pointer to the WaveFile structure.
 *  return:         A WaveError value, see {enum _WaveError}.
 */
WavError wav_errno(WavFile* self);

/** function:       wave_set_format
 *  description:    Set the format code
 *  parameters:
 *      self:       The WaveFile object
 *      format:     The format code, which should be one of WAVE_FORMAT_*
 *  return:         None
 *  remarks:        All data will be cleared after the call
 *                  {wav_errno} can be used to get the error code if there is an error.
 */
void wav_set_format(WavFile* self, uint16_t format);

/** function:       wave_set_num_channels
 *  description:    Set the number of channels
 *  parameters:
 *      self:           The WaveFile object
 *      num_channels:   The number of channels
 *  return:         None
 *  remarks:        All data will be cleared after the call
 *                  {wav_errno} can be used to get the error code if there is an error.
 */
void wav_set_num_channels(WavFile* self, uint16_t num_channels);

/** function:       wave_set_sample_rate
 *  description:    Set the sample rate
 *  parameters:
 *      self:           The WaveFile object
 *      sample_rate:    The sample rate
 *  return:         None
 *  remarks:        All data will be cleared after the call
 *                  {wav_errno} can be used to get the error code if there is an error.
 */
void wav_set_sample_rate(WavFile* self, uint32_t sample_rate);

/** function:       wave_set_valid_bits_per_sample
 *  description:    get the number of valid bits per sample
 *  parameters:
 *      self:       The WaveFile object
 *      bits:       The value of valid bits to set
 *  return:         None
 *  remarks:        If {bits} is 0 or larger than 8*{sample_size}, an error will occur.
 *                  All data will be cleared after the call.
 *                  {wav_errno} can be used to get the error code if there is an error.
 */
void wav_set_valid_bits_per_sample(WavFile* self, uint16_t bits);

/** function:       wave_set_sample_size
 *  description:    Set the size (in bytes) per sample
 *  parameters:
 *      self:           the WaveFile object
 *      sample_size:    the sample size value
 *  return:         None
 *  remarks:        When this function is called, the {BitsPerSample} and {ValidBitsPerSample}
 *                  fields in the wave file will be set to 8*{sample_size}.
 *                  All data will be cleared after the call.
 *                  {wav_errno} can be used to get the error code if there is an error.
 */
void wav_set_sample_size(WavFile* self, size_t sample_size);

/**
 */
uint16_t wav_get_format(WavFile* self);
uint16_t wav_get_num_channels(WavFile* self);
uint32_t wav_get_sample_rate(WavFile* self);
uint16_t wav_get_valid_bits_per_sample(WavFile* self);
size_t   wav_get_sample_size(WavFile* self);
size_t   wav_get_length(WavFile* self);

#ifdef __cplusplus
}
#endif

#endif /* __WAV_H__ */
