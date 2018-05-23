#include "prices_list_widget.h"

#include "ui/widgets/buttons.h"
#include "lang/lang_keys.h"
#include "styles/style_chat_helpers.h"
#include "styles/style_widgets.h"

namespace ChatHelpers {

class PricesListWidget::Footer : public TabbedSelector::InnerFooter
{
public:
	Footer(not_null<PricesListWidget*> parent);

protected:
	void processPanelHideFinished() override;
	void resizeEvent(QResizeEvent* e) override;
	void customizeClick();

private:
	not_null<PricesListWidget*> _parent;
	object_ptr<Ui::LinkButton> _link;
};

PricesListWidget::Footer::Footer(not_null<PricesListWidget*> parent)
	:  InnerFooter(parent)
	, _parent(parent)
	, _link(object_ptr<Ui::LinkButton>(this, lang(lng_prices_customize_list), st::largeLinkButton))
{
	_link->setClickedCallback([this] { customizeClick(); });
}

void PricesListWidget::Footer::resizeEvent(QResizeEvent* e)
{
	_link->move(rect().center() - _link->rect().center());
}

void PricesListWidget::Footer::processPanelHideFinished()
{
}

void PricesListWidget::Footer::customizeClick()
{
	//TODO: bettergram: realize PricesListWidget::Footer::customizeClick() method
}

PricesListWidget::PricesListWidget(QWidget* parent, not_null<Window::Controller*> controller)
	: Inner(parent, controller)
{
}

void PricesListWidget::refreshRecent()
{
}

void PricesListWidget::clearSelection()
{
}

object_ptr<TabbedSelector::InnerFooter> PricesListWidget::createFooter()
{
	Expects(_footer == nullptr);

	auto res = object_ptr<Footer>(this);

	_footer = res;
	return std::move(res);
}

TabbedSelector::InnerFooter* PricesListWidget::getFooter() const
{
	return _footer;
}

int PricesListWidget::countDesiredHeight(int newWidth)
{
	return 1;
}

void PricesListWidget::paintEvent(QPaintEvent *event) {
	Painter painter(this);
	QRect r = event ? event->rect() : rect();

	if (r != rect()) {
		painter.setClipRect(r);
	}

	painter.fillRect(r, st::emojiPanBg);

//	enumerateSections([this, &painter, r, fromColumn, toColumn](const SectionInfo &info) {
//		if (r.top() >= info.rowsBottom) {
//			return true;
//		} else if (r.top() + r.height() <= info.top) {
//			return false;
//		}
//		if (info.section > 0 && r.top() < info.rowsTop) {
//			painter.setFont(st::emojiPanHeaderFont);
//			painter.setPen(st::emojiPanHeaderFg);
//			painter.drawTextLeft(st::emojiPanHeaderLeft - st::buttonRadius, info.top + st::emojiPanHeaderTop, width(), lang(LangKey(lng_emoji_category0 + info.section)));
//		}
//		if (r.top() + r.height() > info.rowsTop) {
//			ensureLoaded(info.section);
//			auto fromRow = floorclamp(r.y() - info.rowsTop, _singleSize.height(), 0, info.rowsCount);
//			auto toRow = ceilclamp(r.y() + r.height() - info.rowsTop, _singleSize.height(), 0, info.rowsCount);
//			for (auto i = fromRow; i < toRow; ++i) {
//				for (auto j = fromColumn; j < toColumn; ++j) {
//					auto index = i * _columnCount + j;
//					if (index >= info.count) break;

//					auto selected = (!_picker->isHidden() && info.section * MatrixRowShift + index == _pickerSel) || (info.section * MatrixRowShift + index == _selected);

//					auto w = QPoint(_rowsLeft + j * _singleSize.width(), info.rowsTop + i * _singleSize.height());
//					if (selected) {
//						auto tl = w;
//						if (rtl()) tl.setX(width() - tl.x() - _singleSize.width());
//						App::roundRect(painter, QRect(tl, _singleSize), st::emojiPanHover, StickerHoverCorners);
//					}
//					auto sourceRect = QRect(_emoji[info.section][index]->x() * _esize, _emoji[info.section][index]->y() * _esize, _esize, _esize);
//					auto imageLeft = w.x() + (_singleSize.width() - (_esize / cIntRetinaFactor())) / 2;
//					auto imageTop = w.y() + (_singleSize.height() - (_esize / cIntRetinaFactor())) / 2;
//					painter.drawPixmapLeft(imageLeft, imageTop, width(), App::emojiLarge(), sourceRect);
//				}
//			}
//		}
//		return true;
//	});
}

} // namespace ChatHelpers
