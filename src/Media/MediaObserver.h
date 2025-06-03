#ifndef MEDIA_OBSERVER_H
#define MEDIA_OBSERVER_H

namespace Media {

class AbstractMedia;

class MediaObserver{
public:
    virtual void notify(const AbstractMedia& media) = 0;

    virtual ~MediaObserver() = default;
};

}

#endif