
/*
    Copyright (C) 2011 James McLaughlin

    This file is part of Lacewing.

    Lacewing is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Lacewing is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Lacewing.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "../Common.h"

lw_ws * lw_ws_new (lw_eventpump * eventpump)
    { return (lw_ws *) new Lacewing::Webserver(*(Lacewing::EventPump *) eventpump);
    }
void lw_ws_delete (lw_ws * webserver)
    { delete (Lacewing::Webserver *) webserver;
    }
void lw_ws_host (lw_ws * webserver, long port)
    { ((Lacewing::Webserver *) webserver)->Host(port);
    }
void lw_ws_host_secure (lw_ws * webserver, long port)
    { ((Lacewing::Webserver *) webserver)->HostSecure(port);
    }
void lw_ws_host_filter (lw_ws * webserver, lw_filter * filter)
    { ((Lacewing::Webserver *) webserver)->Host(*(Lacewing::Filter *) filter);
    }
void lw_ws_host_secure_filter (lw_ws * webserver, lw_filter * filter)
    { ((Lacewing::Webserver *) webserver)->HostSecure(*(Lacewing::Filter *) filter);
    }
void lw_ws_unhost (lw_ws * webserver)
    { ((Lacewing::Webserver *) webserver)->Unhost();
    }
void lw_ws_unhost_secure (lw_ws * webserver)
    { ((Lacewing::Webserver *) webserver)->UnhostSecure();
    }
lw_bool lw_ws_hosting (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->Hosting() ? 1 : 0;
    }
lw_bool lw_ws_hosting_secure (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->HostingSecure() ? 1 : 0;
    }
long lw_ws_port (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->Port();
    }
long lw_ws_port_secure (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->SecurePort();
    }
lw_bool lw_ws_load_cert_file (lw_ws * webserver, const char * filename, const char * passphrase)
    { return ((Lacewing::Webserver *) webserver)->LoadCertificateFile(filename, passphrase);
    }
lw_bool lw_ws_load_sys_cert (lw_ws * webserver, const char * store_name, const char * common_name, const char * location)
    { return ((Lacewing::Webserver *) webserver)->LoadSystemCertificate(store_name, common_name, location);
    }
lw_bool lw_ws_cert_loaded (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->CertificateLoaded();
    }
lw_i64 lw_ws_bytes_sent (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->BytesSent();
    }
lw_i64 lw_ws_bytes_received (lw_ws * webserver)
    { return ((Lacewing::Webserver *) webserver)->BytesReceived();
    }
void lw_ws_close_session (lw_ws * webserver, const char * id)
    { ((Lacewing::Webserver *) webserver)->CloseSession(id);
    }
void lw_ws_enable_manual_finish (lw_ws * webserver)
    { ((Lacewing::Webserver *) webserver)->EnableManualRequestFinish();
    }
lw_addr* lw_ws_req_addr (lw_ws_req * request)
    { return (lw_addr *) &((Lacewing::Webserver::Request *) request)->GetAddress();
    }
lw_bool lw_ws_req_secure (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->Secure();
    }
const char* lw_ws_req_url (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->URL();
    }
const char* lw_ws_req_hostname (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->Hostname();
    }
void lw_ws_req_disconnect (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->Disconnect();
    } 
void lw_ws_req_set_redirect (lw_ws_req * request, const char * url)
    { ((Lacewing::Webserver::Request *) request)->SetRedirect(url);
    }
void lw_ws_req_set_response_type (lw_ws_req * request, long status_code, const char * message)
    { ((Lacewing::Webserver::Request *) request)->SetResponseType(status_code, message);
    }
void lw_ws_req_set_mime_type (lw_ws_req * request, const char * mime_type)
    { ((Lacewing::Webserver::Request *) request)->SetMimeType(mime_type);
    }
void lw_ws_req_guess_mime_type (lw_ws_req * request, const char * filename)
    { ((Lacewing::Webserver::Request *) request)->GuessMimeType(filename);
    }
void lw_ws_req_set_charset (lw_ws_req * request, const char * charset)
    { ((Lacewing::Webserver::Request *) request)->SetCharset(charset);
    }
void lw_ws_req_send_text (lw_ws_req * request, const char * data)
    { ((Lacewing::Webserver::Request *) request)->Send(data);
    }
void lw_ws_req_send_text_const (lw_ws_req * request, const char * data)
    { ((Lacewing::Webserver::Request *) request)->SendConstant(data);
    }
void lw_ws_req_send (lw_ws_req * request, const char * data, long size)
    { ((Lacewing::Webserver::Request *) request)->Send(data, size);
    }
void lw_ws_req_send_const (lw_ws_req * request, const char * data, long size)
    { ((Lacewing::Webserver::Request *) request)->SendConstant(data, size);
    }
void lw_ws_req_sendfile (lw_ws_req * request, const char * filename)
    { ((Lacewing::Webserver::Request *) request)->SendFile(filename);
    }
void lw_ws_req_reset (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->Reset();
    }
void lw_ws_req_finish (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->Finish();
    }
lw_i64 lw_ws_req_last_modified (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->LastModified();
    }
void lw_ws_req_set_last_modified (lw_ws_req * request, lw_i64 modified)
    { ((Lacewing::Webserver::Request *) request)->LastModified(modified);
    }
void lw_ws_req_set_unmodified (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->SetUnmodified();
    }
void lw_ws_req_set_header (lw_ws_req * request, const char * name, const char * value)
    { ((Lacewing::Webserver::Request *) request)->Header(name, value);
    }
const char* lw_ws_req_header (lw_ws_req * request, const char * name)
    { return ((Lacewing::Webserver::Request *) request)->Header(name);
    }
void lw_ws_req_set_cookie (lw_ws_req * request, const char * name, const char * value)
    { ((Lacewing::Webserver::Request *) request)->Cookie(name, value);
    }
const char* lw_ws_req_cookie (lw_ws_req * request, const char * name)
    { return ((Lacewing::Webserver::Request *) request)->Cookie(name);
    }
const char* lw_ws_req_session_id (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->Session();
    }
void lw_ws_req_session_write (lw_ws_req * request, const char * name, const char * value)
    { ((Lacewing::Webserver::Request *) request)->Session(name, value);
    }
const char* lw_ws_req_session_read (lw_ws_req * request, const char * name)
    { return ((Lacewing::Webserver::Request *) request)->Session(name);
    }
void lw_ws_req_session_close (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->CloseSession();
    }
const char* lw_ws_req_GET (lw_ws_req * request, const char * name)
    { return ((Lacewing::Webserver::Request *) request)->GET(name);
    }
const char* lw_ws_req_POST (lw_ws_req * request, const char * name)
    { return ((Lacewing::Webserver::Request *) request)->POST(name);
    }
void lw_ws_req_disable_cache (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->DisableCache();
    }
/*void lw_ws_req_enable_dl_resuming (lw_ws_req * request)
    { ((Lacewing::Webserver::Request *) request)->EnableDownloadResuming();
    }
lw_i64 lw_ws_req_reqrange_begin (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->RequestedRangeBegin();
    }
lw_i64 lw_ws_req_reqrange_end (lw_ws_req * request)
    { return ((Lacewing::Webserver::Request *) request)->RequestedRangeEnd();
    }
void lw_ws_req_set_outgoing_range (lw_ws_req * request, lw_i64 begin, lw_i64 end)
    { ((Lacewing::Webserver::Request *) request)->SetOutgoingRange(begin, end);
    }*/
const char* lw_ws_upload_form_el_name (lw_ws_upload * upload)
    { return ((Lacewing::Webserver::Upload *) upload)->FormElementName();
    }
const char* lw_ws_upload_filename (lw_ws_upload * upload)
    { return ((Lacewing::Webserver::Upload *) upload)->Filename();
    }
const char* lw_ws_upload_header (lw_ws_upload * upload, const char * name)
    { return ((Lacewing::Webserver::Upload *) upload)->Header(name);
    }
void lw_ws_upload_set_autosave (lw_ws_upload * upload)
    { ((Lacewing::Webserver::Upload *) upload)->SetAutoSave();
    }
const char* lw_ws_upload_autosave_fname (lw_ws_upload * upload)
    { return ((Lacewing::Webserver::Upload *) upload)->GetAutoSaveFilename();
    }

AutoHandlerFlat(Lacewing::Webserver, lw_ws, Get, get)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, Post, post)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, Head, head)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, Error, error)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, Connect, connect)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, Disconnect, disconnect)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, UploadStart, upload_start)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, UploadChunk, upload_chunk)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, UploadDone, upload_done)
AutoHandlerFlat(Lacewing::Webserver, lw_ws, UploadPost, upload_post)

void lw_ws_req_sendf (lw_ws_req * request, const char * format, ...)
{
    va_list args;
    va_start (args, format);
    
    char * data;
    int size = LacewingFormat(data, format, args);
    
    if(size > 0)
        ((Lacewing::Webserver::Request *) request)->Send(data, size);

    va_end (args);
}