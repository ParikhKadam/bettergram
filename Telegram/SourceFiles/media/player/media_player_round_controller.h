/*
This file is part of Bettergram.

For license and copyright information please follow this link:
https://github.com/bettergram/bettergram/blob/master/LEGAL
*/
#pragma once

class HistoryItem;
class AudioMsgId;

namespace Window {
class Controller;
} // namespace Window

namespace Media {
namespace View {
class PlaybackProgress;
} // namespace View
} // namespace Media

namespace Media {
namespace Player {

struct TrackState;
enum class State;

class RoundController
	: public base::has_weak_ptr
	, private base::Subscriber {
	struct CreateTag;

public:
	static std::unique_ptr<RoundController> TryStart(
		not_null<Window::Controller*> parent,
		not_null<HistoryItem*> item);

	FullMsgId contextId() const;
	void pauseResume();
	Clip::Reader *reader() const;
	View::PlaybackProgress *playback() const;

	rpl::lifetime &lifetime();

	RoundController(
		CreateTag&&,
		not_null<Window::Controller*> parent,
		not_null<HistoryItem*> item);
	~RoundController();

private:
	void stop(State state);
	bool checkReaderState();
	void callback(Clip::Notification notification);
	void handleAudioUpdate(const TrackState &audioId);

	not_null<Window::Controller*> _parent;
	not_null<DocumentData*> _data;
	not_null<HistoryItem*> _context;
	Clip::ReaderPointer _reader;
	std::unique_ptr<View::PlaybackProgress> _playbackProgress;

	rpl::lifetime _lifetime;

};

} // namespace Player
} // namespace Media
