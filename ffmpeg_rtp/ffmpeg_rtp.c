AVFormatContext *fmtctx;
AVStream *video_st;
AVCodec *video_codec;
const int FPS = 25;		/* 25 images/s */
const char *RDIP = "127.0.0.1";
unsigned int RDPORT = 5678;
const unsigned int OUTWIDTH = 720;
const unsigned int OUTHEIGHT = 480;
av_register_all ();
avformat_network_init ();
AVStream *
add_video_stream (AVFormatContext * oc, AVCodec ** codec,
		  enum AVCodecID codec_id);
static void
fill_yuv_image (AVPicture * pict, int frame_index, int width, int height);
int
main ()
{
  fmtctx = avformat_alloc_context ();
  fmtctx->oformat = av_guess_format ("rtp", NULL, NULL);
  snprintf (fmtctx->filename, sizeof (fmtctx->filename), "rtp://%s:%d", RDIP,
	    RDPORT);
  avio_open (&fmtctx->pb, fmtctx->filename, AVIO_FLAG_WRITE);
  video_st = NULL;
  video_st = add_video_stream (fmtctx, &video_codec, AV_CODEC_ID_H264);
  // OPEN THE CODE
  avcodec_open2 (video_st->codec, video_codec, NULL);
  /* Write the stream header, if any. */
  avformat_write_header (fmtctx, NULL);

  AVFrame *m_pYUVFrame = avcodec_alloc_frame ();
  while (1)
    {
      fill_yuv_image (m_pYUVFrame, video_st->codec->frame_number, OUTWIDTH,
		      OUTHEIGHT);
/* encode the image */
      AVPacket pkt;
      int got_output = 0;
      av_init_packet (&pkt);
      pkt.data = NULL;		// packet data will be allocated by the encoder
      pkt.size = 0;
      pkt.pts = AV_NOPTS_VALUE;
      pkt.dts = AV_NOPTS_VALUE;
      m_pYUVFrame->pts = video_st->codec->frame_number;
      ret = avcodec_encode_video2 (c, &pkt, frame, &got_output);
      if (ret < 0)
	{
	  fprintf (stderr, "Error encoding video frame: %s\n",
		   av_err2str (ret));
	  exit (1);
	}
/* If size is zero, it means the image was buffered. */
      if (got_output)
	{
	  if (c->coded_frame->key_frame)
	    pkt.flags |= AV_PKT_FLAG_KEY;
	  pkt.stream_index = st->index;
	  if (pkt.pts != AV_NOPTS_VALUE)
	    {
	      pkt.pts =
		av_rescale_q (pkt.pts, video_st->codec->time_base,
			      video_st->time_base);
	    }
	  if (pkt.dts != AV_NOPTS_VALUE)
	    {
	      pkt.dts =
		av_rescale_q (pkt.dts, video_st->codec->time_base,
			      video_st->time_base);
	    }
/* Write the compressed frame to the media file. */
	  ret = av_interleaved_write_frame (oc, &pkt);
	}
      else
	{
	  ret = 0;
	}
    }


//print sdp info
  char sdp[2048];
  av_sdp_create (&fmtctx, 1, sdp, sizeof (sdp));
  printf ("%s\n", sdp);
  fflush (stdout);

  avcodec_free_frame (&m_pYUVFrame);
  av_write_trailer (fmtctx);
/* Free the streams. */
  for (unsigned int i = 0; i < fmtctx->nb_streams; i++)
    {
      av_freep (&fmtctx->streams->codec);
      av_freep (&fmtctx->streams);
    }
  if (!(fmtctx->oformat->flags & AVFMT_NOFILE))
/* Close the output file. */
    avio_close (fmtctx->pb);
/*free the stream */
  av_free (fmtctx);
}

AVStream *
add_video_stream (AVFormatContext * oc, AVCodec ** codec,
		  enum AVCodecID codec_id)
{
  AVCodecContext *c;
  AVStream *st;
/* find the video encoder */
  *codec = avcodec_find_encoder (codec_id);
  st = avformat_new_stream (oc, *codec);
  c = st->codec;
  avcodec_get_context_defaults3 (c, *codec);
  c->codec_id = codec_id;
  c->width = OUTWIDTH;
  c->height = OUTHEIGHT;
  c->time_base.den = FPS;
  c->time_base.num = 1;
  c->pix_fmt = PIX_FMT_YUV420P;
  if (oc->oformat->flags & AVFMT_GLOBALHEADER)
    c->flags |= CODEC_FLAG_GLOBAL_HEADER;
  av_opt_set (c->priv_data, "preset", "ultrafast", 0);
  av_opt_set (c->priv_data, "tune", "stillimage,fastdecode,zerolatency", 0);
  av_opt_set (c->priv_data, "x264opts",
	      "crf=26:vbv-maxrate=728:vbv-bufsize=364:keyint=25", 0);
  return st;
}

/* Prepare a dummy image. */
static void
fill_yuv_image (AVPicture * pict, int frame_index, int width, int height)
{
  int x, y, i;
  i = frame_index;
/* Y */
  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++)
      pict->data[0][y * pict->linesize[0] + x] = x + y + i * 3;
/* Cb and Cr */
  for (y = 0; y < height / 2; y++)
    {
      for (x = 0; x < width / 2; x++)
	{
	  pict->data[1][y * pict->linesize[1] + x] = 128 + y + i * 2;
	  pict->data[2][y * pict->linesize[2] + x] = 64 + x + i * 5;
	}
    }
}
