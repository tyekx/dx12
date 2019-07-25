#include "math.h"


const Bool1 Bool1::zero(false);
const Bool1 Bool1::xUnit(true);
const Bool1 Bool1::one(true);

const Bool2 Bool2::zero(false, false);
const Bool2 Bool2::xUnit(true, false);
const Bool2 Bool2::yUnit(false, true);
const Bool2 Bool2::one(true, true);

const Bool3 Bool3::zero(false, false, false);
const Bool3 Bool3::xUnit(true, false, false);
const Bool3 Bool3::yUnit(false, true, false);
const Bool3 Bool3::zUnit(false, false, true);
const Bool3 Bool3::one(true, true, true);

const Bool4 Bool4::zero(false, false, false, false);
const Bool4 Bool4::xUnit(true, false, false, false);
const Bool4 Bool4::yUnit(false, true, false, false);
const Bool4 Bool4::zUnit(false, false, true, false);
const Bool4 Bool4::wUnit(false, false, false, true);
const Bool4 Bool4::one(true, true, true, true);


const Int1 Int1::zero(0);
const Int1 Int1::xUnit(1);
const Int1 Int1::one(1);

const Int2 Int2::zero(0, 0);
const Int2 Int2::xUnit(1, 0);
const Int2 Int2::yUnit(0, 1);
const Int2 Int2::one(1, 1);

const Int3 Int3::zero(0, 0, 0);
const Int3 Int3::xUnit(1, 0, 0);
const Int3 Int3::yUnit(0, 1, 0);
const Int3 Int3::zUnit(0, 0, 1);
const Int3 Int3::one(1, 1, 1);

const Int4 Int4::zero(0, 0, 0, 0);
const Int4 Int4::xUnit(1, 0, 0, 0);
const Int4 Int4::yUnit(0, 1, 0, 0);
const Int4 Int4::zUnit(0, 0, 1, 0);
const Int4 Int4::wUnit(0, 0, 0, 1);
const Int4 Int4::one(1, 1, 1, 1);


const Float1 Float1::zero(0.0f);
const Float1 Float1::xUnit(1.0f);
const Float1 Float1::one(1.0f);

const Float2 Float2::zero(0.0f, 0.0f);
const Float2 Float2::xUnit(1.0f, 0.0f);
const Float2 Float2::yUnit(0.0f, 1.0f);
const Float2 Float2::one(1.0f, 1.0f);

const Float3 Float3::zero(0.0f, 0.0f, 0.0f);
const Float3 Float3::xUnit(1.0f, 0.0f, 0.0f);
const Float3 Float3::yUnit(0.0f, 1.0f, 0.0f);
const Float3 Float3::zUnit(0.0f, 0.0f, 1.0f);
const Float3 Float3::one(1.0f, 1.0f, 1.0f);

const Float3 Float3::black				(0.0f, 0.0f, 0.0f);
const Float3 Float3::navy				(0.0f, 0.0f, 0.5f);
const Float3 Float3::blue				(0.0f, 0.0f, 1.0f);
const Float3 Float3::darkGreen			(0.0f, 0.5f, 0.0f);
const Float3 Float3::teal				(0.0f, 0.5f, 0.5f);
const Float3 Float3::azure				(0.0f, 0.5f, 1.0f);
const Float3 Float3::green				(0.0f, 1.0f, 0.0f);
const Float3 Float3::cyan				(0.0f, 1.0f, 1.0f);
const Float3 Float3::maroon				(0.5f, 0.0f, 0.0f);
const Float3 Float3::purple				(0.5f, 0.0f, 0.5f);
const Float3 Float3::slateBlue			(0.5f, 0.0f, 1.0f);
const Float3 Float3::olive				(0.5f, 0.5f, 0.0f);
const Float3 Float3::gray				(0.5f, 0.5f, 0.5f);
const Float3 Float3::cornflower			(0.5f, 0.5f, 1.0f);
const Float3 Float3::aquamarine			(0.5f, 1.0f, 0.75f);
const Float3 Float3::red				(1.0f, 0.0f, 0.0f);
const Float3 Float3::deepPink			(1.0f, 0.0f, 0.5f);
const Float3 Float3::magenta			(1.0f, 0.0f, 1.0f);
const Float3 Float3::orange				(1.0f, 0.5f, 0.0f);
const Float3 Float3::coral				(1.0f, 0.5f, 0.31f);
const Float3 Float3::mallow				(1.0f, 0.5f, 1.0f);
const Float3 Float3::yellow				(1.0f, 1.0f, 0.0f);
const Float3 Float3::gold				(1.0f, 1.0f, 0.5f);
const Float3 Float3::white				(1.0f, 1.0f, 1.0f);
const Float3 Float3::silver				(0.75f, 0.75f, 0.75f);


const Float4 Float4::zero(0.0f, 0.0f, 0.0f, 0.0f);
const Float4 Float4::xUnit(1.0f, 0.0f, 0.0f, 0.0f);
const Float4 Float4::yUnit(0.0f, 1.0f, 0.0f, 0.0f);
const Float4 Float4::zUnit(0.0f, 0.0f, 1.0f, 0.0f);
const Float4 Float4::wUnit(0.0f, 0.0f, 0.0f, 1.0f);
const Float4 Float4::one(1.0f, 1.0f, 1.0f, 1.0f);

const Float4 Float4::identity(0.0f, 0.0f, 0.0f, 1.0f);

const Float4x4 Float4x4::identity(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);